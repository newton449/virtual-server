package com.newton449.virtualserverclient.user.client;

import com.google.gwt.activity.shared.AbstractActivity;
import com.google.gwt.event.shared.EventBus;
import com.google.gwt.user.client.ui.AcceptsOneWidget;

/**
 *
 * @author Steven
 */
public class NotFoundActivity extends AbstractActivity {

    private NotFoundPage view = new NotFoundPage();

    @Override
    public void start(AcceptsOneWidget panel, EventBus eventBus) {
        panel.setWidget(view);
    }
}
