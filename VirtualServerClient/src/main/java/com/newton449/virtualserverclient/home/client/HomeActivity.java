package com.newton449.virtualserverclient.home.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.user.client.ui.AcceptsOneWidget;

/**
 * An activity to show "Home" page.
 *
 * @author Steven
 */
public class HomeActivity extends AbstractActivity {

    HomePage view = new HomePage();

    @Override
    public void start(AcceptsOneWidget panel, EventBus eventBus) {
        panel.setWidget(view);
    }

}
