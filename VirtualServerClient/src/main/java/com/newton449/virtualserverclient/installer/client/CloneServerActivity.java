package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.core.client.JsonUtils;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.json.client.JSONObject;
import com.google.gwt.user.client.ui.AcceptsOneWidget;
import com.newton449.virtualserverclient.installer.client.model.ModulesModel;
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
            public void onNext(ModulesModel model) {
                onSubmitChooseModules(model);
            }
        });

        checkDependenciesPage.setPresenter(new CloneServerCheckDependenciesPage.Presenter() {

            @Override
            public void onPrevious(ModulesModel model) {
                onReturnChooseModules(model);
            }

            @Override
            public void onNext(ModulesModel model) {
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

        // show loading page
        // show choose modules page
        // if "next" clicked
        // check form
        // send form, get final modules
        // if "next" clicked
        // send form
        // get file name
        // show a page for building
        // ask the server for building state
        // show download page
        // if "next" clicked
        // show configure & run server page
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
                    ModulesModel initialModel = JsonUtils.safeEval(text);
                    showChooseModulesPage(initialModel);
                } catch (IllegalArgumentException ex) {
                    // show error message with some part of text
                    errorPanel.showError("Failed to get initial modules. Got :" + (text.length() > 20 ? text.substring(0, 20) + "..." : text));
                }
            }
        });
        sender.send();
    }

    private void showChooseModulesPage(ModulesModel initialModel) {
        chooseModulesPage.setModel(initialModel);
        chooseModulesPage.showError(null);
        container.setWidget(chooseModulesPage);
    }

    private ModulesModel buildTestModules() {
        String data = "{\n"
                + "    \"versions\": [\n"
                + "        \"Windows\",\n"
                + "        \"Linux x86\",\n"
                + "        \"Linux x64\"\n"
                + "    ],\n"
                + "    \"modules\": [\n"
                + "        {\n"
                + "            \"name\": \"Main Program\",\n"
                + "            \"description\": \"The main server program.\",\n"
                + "            \"versionStates\": [\n"
                + "                {\n"
                + "                    \"enabled\": false,\n"
                + "                    \"selected\": true\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": false,\n"
                + "                    \"selected\": false\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": false,\n"
                + "                    \"selected\": false\n"
                + "                }\n"
                + "            ]\n"
                + "        },\n"
                + "        {\n"
                + "            \"name\": \"Installer\",\n"
                + "            \"description\": \"Allows others to clone your server.\",\n"
                + "            \"versionStates\": [\n"
                + "                {\n"
                + "                    \"enabled\": true,\n"
                + "                    \"selected\": true\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": true,\n"
                + "                    \"selected\": false\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": true,\n"
                + "                    \"selected\": false\n"
                + "                }\n"
                + "            ]\n"
                + "        },\n"
                + "        {\n"
                + "            \"name\": \"File Manager\",\n"
                + "            \"description\": \"Supports uploading and downloading files.\",\n"
                + "            \"versionStates\": [\n"
                + "                {\n"
                + "                    \"enabled\": true,\n"
                + "                    \"selected\": true\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": false,\n"
                + "                    \"selected\": false\n"
                + "                },\n"
                + "                {\n"
                + "                    \"enabled\": false,\n"
                + "                    \"selected\": false\n"
                + "                }\n"
                + "            ]\n"
                + "        }\n"
                + "    ]\n"
                + "}";
        /*
         {
         "versions": [
         "Windows",
         "Linux x86",
         "Linux x64"
         ],
         "modules": [
         {
         "name": "Main Program",
         "description": "The main server program.",
         "versionStates": [
         {
         "enabled": false,
         "selected": true
         },
         {
         "enabled": false,
         "selected": false
         },
         {
         "enabled": false,
         "selected": false
         }
         ]
         },
         {
         "name": "Installer",
         "description": "Allows others to clone your server.",
         "versionStates": [
         {
         "enabled": true,
         "selected": true
         },
         {
         "enabled": true,
         "selected": false
         },
         {
         "enabled": true,
         "selected": false
         }
         ]
         },
         {
         "name": "File Manager",
         "description": "Supports uploading and downloading files.",
         "versionStates": [
         {
         "enabled": true,
         "selected": true
         },
         {
         "enabled": false,
         "selected": false
         },
         {
         "enabled": false,
         "selected": false
         }
         ]
         }
         ]
         }
         */
        return JsonUtils.safeEval(data);
    }

    private void onSubmitChooseModules(ModulesModel model) {
        chooseModulesPage.lockUI();

        // build a string for the json model
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
                    ModulesModel newModel = JsonUtils.safeEval(text);
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

    private void onReturnChooseModules(ModulesModel model) {
        container.setWidget(chooseModulesPage);
        chooseModulesPage.setModel(model);
    }

    private void onSubmitCheckModules(ModulesModel model) {
        container.setWidget(downloadServerPage);
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
