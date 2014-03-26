package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;

/**
 * A page to show information about this web site.
 *
 * @author Steven
 */
public class AboutPage extends Composite {

    private static final AboutPageUiBinder uiBinder = GWT.create(AboutPageUiBinder.class);

    interface AboutPageUiBinder extends UiBinder<Widget, AboutPage> {
    }

    public AboutPage() {
        initWidget(uiBinder.createAndBindUi(this));
    }
}
