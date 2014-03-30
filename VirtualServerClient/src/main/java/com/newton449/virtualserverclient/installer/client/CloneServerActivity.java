package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.core.client.JsonUtils;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.json.client.JSONObject;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.ui.AcceptsOneWidget;
import com.newton449.virtualserverclient.installer.client.model.CheckingDependenciesModel;
import com.newton449.virtualserverclient.installer.client.model.CreatingServerModel;
import com.newton449.virtualserverclient.installer.client.model.FileKeyModel;
import com.newton449.virtualserverclient.installer.client.model.FileStatusModel;
import com.newton449.virtualserverclient.installer.client.model.ModulesSelectingModel;
import com.newton449.virtualserverclient.user.client.AbstractRequestCallback;
import com.newton449.virtualserverclient.user.client.GlobalMessagePanel;
import com.newton449.virtualserverclient.user.client.RequestSender;

/**
 * An activity for users to clone the server. The cloning process contains four
 * steps: ChooseModules, CheckDependencies, DownloadServer & ConfigureRunServer.
 * This activity controls logics for all the steps.
 *
 * @author Steven
 */
public class CloneServerActivity extends AbstractActivity {

    private final CloneServerChooseModulesPage chooseModulesPage = new CloneServerChooseModulesPage();
    private final CloneServerCheckDependenciesPage checkDependenciesPage = new CloneServerCheckDependenciesPage();
    private final CloneServerDownloadServerPage downloadServerPage = new CloneServerDownloadServerPage();
    private final CloneServerConfigureRunServerPage configureRunServerPage = new CloneServerConfigureRunServerPage();
    private AcceptsOneWidget container;

    public CloneServerActivity() {
        // set actions
        chooseModulesPage.setPresenter(new CloneServerChooseModulesPage.Presenter() {

            @Override
            public void onNext(ModulesSelectingModel model) {
                onSubmitChooseModules(model);
            }
        });

        checkDependenciesPage.setPresenter(new CloneServerCheckDependenciesPage.Presenter() {

            @Override
            public void onPrevious(ModulesSelectingModel model) {
                onReturnChooseModules(model);
            }

            @Override
            public void onNext(CreatingServerModel model) {
                onSubmitCheckModules(model);
            }
        });

        downloadServerPage.setPresenter(new CloneServerDownloadServerPage.Presenter() {

            @Override
            public void onPrevious() {
                onReturnCheckDependenciesPage();
            }

            @Override
            public void onNext() {
                onGoToConfigureRunServerPage();
            }
        });

        configureRunServerPage.setPresenter(new CloneServerConfigureRunServerPage.Presenter() {

            @Override
            public void onPrevious() {
                onReturnDownloadServerPage();
            }
        });
    }

    @Override
    public void start(AcceptsOneWidget panel, EventBus eventBus) {
        container = panel;
        loadInitialModules();
    }

    private void loadInitialModules() {
        // get modules list
        RequestSender sender = new RequestSender(RequestBuilder.GET, "/installer/modules_list");
        final GlobalMessagePanel errorPanel = new GlobalMessagePanel();
        sender.setErrorHandler(errorPanel);
        sender.setRequestData(null);
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                // convert response text to model
                String text = response.getText();
                try {
                    ModulesSelectingModel initialModel = JsonUtils.safeEval(text);
                    showChooseModulesPage(initialModel);
                } catch (IllegalArgumentException ex) {
                    // show error message with some part of text
                    errorPanel.showError("Failed to get initial modules. Got :" + (text.length() > 20 ? text.substring(0, 20) + "..." : text));
                }
            }
        });
        sender.send();
    }

    private void showChooseModulesPage(ModulesSelectingModel initialModel) {
        chooseModulesPage.setModel(initialModel);
        chooseModulesPage.showError(null);
        container.setWidget(chooseModulesPage);
    }

    private void onSubmitChooseModules(ModulesSelectingModel model) {
        chooseModulesPage.lockUI();

        // build a string of the json model
        String data = new JSONObject(model).toString();

        // send a request to server
        RequestSender sender = new RequestSender(RequestBuilder.POST, "/installer/check_dependencies");
        sender.setErrorHandler(chooseModulesPage);
        sender.setRequestData(data);
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                chooseModulesPage.unlockUI();
                // parse response text to get model with dependencies
                String text = response.getText();
                try {
                    CheckingDependenciesModel newModel = JsonUtils.safeEval(text);
                    // show CheckDependenciesPage
                    checkDependenciesPage.setModel(newModel);
                    checkDependenciesPage.showError(null);
                    container.setWidget(checkDependenciesPage);
                } catch (IllegalArgumentException ex) {
                    chooseModulesPage.showError("Failed to get final modules. Got :" + (text.length() > 40 ? text.substring(0, 40) + "..." : text));
                }
            }

            @Override
            public boolean onErrorAny(Request request) {
                chooseModulesPage.unlockUI();
                return true;
            }

        });
        sender.send();
    }

    private void onReturnChooseModules(ModulesSelectingModel model) {
        container.setWidget(chooseModulesPage);
        chooseModulesPage.setModel(model);
    }

    private void onSubmitCheckModules(CreatingServerModel model) {
        checkDependenciesPage.lockUI();
        checkDependenciesPage.showError(null);

        // build a string of the model
        String data = new JSONObject(model).toString();

        // send a request to server
        RequestSender sender = new RequestSender(RequestBuilder.POST, "/installer/create_server");
        sender.setErrorHandler(checkDependenciesPage);
        sender.setRequestData(data);
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                checkDependenciesPage.unlockUI();
                // parse response to model
                String text = response.getText();
                try {
                    FileKeyModel key = JsonUtils.safeEval(text);
                    // show DownloadServer page
                    showDownloadServerPage(key);
                } catch (IllegalArgumentException ex) {
                    checkDependenciesPage.showError("Failed to get final modules. Got :" + (text.length() > 40 ? text.substring(0, 40) + "..." : text));
                }
            }

            @Override
            public boolean onErrorAny(Request request) {
                checkDependenciesPage.unlockUI();
                return true;
            }

        });
        sender.send();
    }

    private Timer timer;
    RequestSender checkingFileSender;

    private void showDownloadServerPage(FileKeyModel key) {
        // show DownloadServer page
        downloadServerPage.setDownloadable(false);
        container.setWidget(downloadServerPage);

        // send request to get file url or creating state
        checkingFileSender = new RequestSender(RequestBuilder.POST, "/installer/get_url");
        checkingFileSender.setErrorHandler(downloadServerPage);
        String data = new JSONObject(key).toString();
        checkingFileSender.setRequestData(data);
        checkingFileSender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                String text = response.getText();
                try {
                    FileStatusModel url = JsonUtils.safeEval(text);
                    if (url.getFileUrl() == null) {
                        // it is still in process
                        downloadServerPage.setProgress(url.getPercentage());
                        timer.schedule(url.getWaitingMillisecond());
                    } else {
                        // finished
                        downloadServerPage.setProgress(url.getPercentage());
                        downloadServerPage.setDownloadUrl(url.getFileUrl());
                        downloadServerPage.setDownloadSize(url.getFileSize());
                        downloadServerPage.setDownloadable(true);
                    }
                } catch (IllegalArgumentException ex) {
                    downloadServerPage.showError("Failed to get final modules. Got :" + (text.length() > 40 ? text.substring(0, 40) + "..." : text));
                }
            }
        });
        timer = new Timer() {

            @Override
            public void run() {
                downloadServerPage.showError(null);
                checkingFileSender.send();
            }
        };
        timer.run();
    }

    private void onReturnCheckDependenciesPage() {
        container.setWidget(checkDependenciesPage);
    }

    private void onGoToConfigureRunServerPage() {
        container.setWidget(configureRunServerPage);
    }

    private void onReturnDownloadServerPage() {
        container.setWidget(downloadServerPage);
    }
}
