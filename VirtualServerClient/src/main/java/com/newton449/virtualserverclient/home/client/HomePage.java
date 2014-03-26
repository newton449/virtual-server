package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;

/**
 * A page which is the index of the whole web site.
 *
 * @author Steven
 */
public class HomePage extends Composite {

    private static HomePageUiBinder uiBinder = GWT.create(HomePageUiBinder.class);

    interface HomePageUiBinder extends UiBinder<Widget, HomePage> {
    }

    public HomePage() {
        initWidget(uiBinder.createAndBindUi(this));
    }
}
