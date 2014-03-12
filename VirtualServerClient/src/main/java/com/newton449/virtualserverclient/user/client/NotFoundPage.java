package com.newton449.virtualserverclient.user.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author Steven
 */
public class NotFoundPage extends Composite {

    private static NotFoundPageUiBinder uiBinder = GWT.create(NotFoundPageUiBinder.class);

    interface NotFoundPageUiBinder extends UiBinder<Widget, NotFoundPage> {
    }

    public NotFoundPage() {
        initWidget(uiBinder.createAndBindUi(this));
    }
}
