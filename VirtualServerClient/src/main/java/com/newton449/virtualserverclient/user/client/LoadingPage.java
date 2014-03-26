package com.newton449.virtualserverclient.user.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author Steven
 */
public class LoadingPage extends Composite {

    private static LoadingPageUiBinder uiBinder = GWT.create(LoadingPageUiBinder.class);

    interface LoadingPageUiBinder extends UiBinder<Widget, LoadingPage> {
    }

    public LoadingPage() {
        initWidget(uiBinder.createAndBindUi(this));
    }
}
