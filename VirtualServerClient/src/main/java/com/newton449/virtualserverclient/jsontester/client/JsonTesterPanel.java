package com.newton449.virtualserverclient.jsontester.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.safehtml.shared.SafeHtml;
import com.google.gwt.safehtml.shared.SafeHtmlBuilder;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.user.client.AbstractRequestCallback;
import com.newton449.virtualserverclient.user.client.GlobalMessagePanel;
import com.newton449.virtualserverclient.user.client.RequestSender;

/**
 *
 * @author Steven
 */
public class JsonTesterPanel extends Composite {

    private static JsonTesterPanelUiBinder uiBinder = GWT.create(JsonTesterPanelUiBinder.class);

    @UiField
    TextBox urlBox;
    @UiField
    TextArea requestArea;
    @UiField
    Button submitButton;
    @UiField
    TextArea responseArea;

    interface JsonTesterPanelUiBinder extends UiBinder<Widget, JsonTesterPanel> {
    }

    public JsonTesterPanel() {
        initWidget(uiBinder.createAndBindUi(this));
        submitButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                onSubmit();
            }
        });
    }

    SafeHtml formatResponse(String text) {
        SafeHtmlBuilder builder = new SafeHtmlBuilder();
        builder.appendEscapedLines(text);
        return builder.toSafeHtml();
    }

    void onSubmit() {
        try {
            submitButton.setEnabled(false);
            String data = requestArea.getValue().trim();
            RequestSender sender = new RequestSender(data.isEmpty() ? RequestBuilder.GET : RequestBuilder.POST, urlBox.getValue());
            sender.setRequestData(data.isEmpty() ? null : data);
            sender.setErrorHandler(new GlobalMessagePanel());
            sender.setCallback(new AbstractRequestCallback() {

                @Override
                public void onSuccess(Request request, Response response) {
                    submitButton.setEnabled(true);
                    responseArea.setText(response.getText());
                }

                @Override
                public boolean onErrorAny(Request request) {
                    submitButton.setEnabled(true);
                    return true;
                }

                @Override
                public void onErrorResponse(Request request, Response response) {
                    responseArea.setText(response.getText());
                }

            });
            sender.send();
        } catch (Exception ex) {
            Window.alert(ex.getMessage());
            submitButton.setEnabled(true);
        }
    }
}
