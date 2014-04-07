package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.client.ui.RootPanel;
import com.newton449.virtualserverclient.user.client.Initializer;
import com.newton449.virtualserverclient.user.client.MainFrame;

/**
 *
 * @author Steven
 */
public class UploadEntry implements EntryPoint {

    @Override
    public void onModuleLoad() {
        Initializer initializer = new Initializer();
        MainFrame frame = new MainFrame();
        initializer.prepare(frame);
        frame.setWidget(new UploadPanel());
        RootPanel.get().add(frame);
    }

}
