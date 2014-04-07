/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FormPanel;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author Steven
 */
public class UploadPanel extends Composite {

    private static UploadPanelUiBinder uiBinder = GWT.create(UploadPanelUiBinder.class);

    interface UploadPanelUiBinder extends UiBinder<Widget, UploadPanel> {
    }

    @UiField
    FormPanel form;
    @UiField
    Button submitButton;

    public UploadPanel() {
        initWidget(uiBinder.createAndBindUi(this));
        submitButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                form.submit();
            }
        });

        form.addSubmitCompleteHandler(new FormPanel.SubmitCompleteHandler() {

            @Override
            public void onSubmitComplete(FormPanel.SubmitCompleteEvent event) {
                Window.alert(event.getResults());
            }
        });
    }
}
