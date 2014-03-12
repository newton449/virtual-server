package com.newton449.virtualserverclient.home.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.user.client.ui.AcceptsOneWidget;

/**
 * An activity to show "About" page.
 *
 * @author Steven
 */
public class AboutActivity extends AbstractActivity {

    @Override
    public void start(AcceptsOneWidget panel, EventBus eventBus) {
        // Show the page.
        panel.setWidget(new AboutPage());
    }

}
