package com.newton449.virtualserverclient.home.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.core.client.JsonUtils;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.user.client.ui.AcceptsOneWidget;
import com.newton449.virtualserverclient.home.client.model.ServerInfoModel;
import com.newton449.virtualserverclient.user.client.AbstractRequestCallback;
import com.newton449.virtualserverclient.user.client.GlobalMessagePanel;
import com.newton449.virtualserverclient.user.client.RequestSender;

/**
 * An activity to show "Home" page. It loads some server information and show it
 * on the page.
 *
 * @author Steven
 */
public class HomeActivity extends AbstractActivity {

    private HomePage view = new HomePage();

    @Override
    public void start(AcceptsOneWidget panel, EventBus eventBus) {
        panel.setWidget(view);

        // retrive server info
        RequestSender sender = new RequestSender(RequestBuilder.GET, "/home/server_info");
        final GlobalMessagePanel errorPanel = new GlobalMessagePanel();
        sender.setErrorHandler(errorPanel);
        sender.setRequestData(null);
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                // convert response text to model
                String text = response.getText();
                ServerInfoModel model;
                try {
                    model = JsonUtils.safeEval(text);
                } catch (IllegalArgumentException ex) {
                    // show error message with some part of text
                    errorPanel.showError("Failed to get initial modules. Got :" + (text.length() > 20 ? text.substring(0, 20) + "..." : text));
                    return;
                }
                view.setModel(model);
            }
        });
        sender.send();
    }

}
