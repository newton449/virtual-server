package com.newton449.virtualserverclient.user.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.AcceptsOneWidget;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.IsWidget;
import com.google.gwt.user.client.ui.SimplePanel;
import com.google.gwt.user.client.ui.Widget;

/**
 * A main frame page for all pages. It provides header panel, slide panel,
 * footer panel and so on. Other pages can put themselves in its center panel.
 *
 * @author Steven
 */
public class MainFrame extends Composite implements AcceptsOneWidget {

    private static final MainFrameUiBinder uiBinder = GWT.create(MainFrameUiBinder.class);

    interface MainFrameResources extends ClientBundle {

        @ClientBundle.Source("MainFrame.css")
        MyCss css();

        interface MyCss extends CssResource {

            String item();

        }
    }

    private static final MainFrameResources RESOURCES = GWT
            .create(MainFrameResources.class);

    static {
        RESOURCES.css().ensureInjected();
    }

    @UiField
    SimplePanel centerPanel;
    @UiField
    FlowPanel menuPanel;

    @Override
    public void setWidget(IsWidget w) {
        centerPanel.setWidget(w);
    }

    interface MainFrameUiBinder extends UiBinder<Widget, MainFrame> {
    }

    public MainFrame() {
        initWidget(uiBinder.createAndBindUi(this));
    }

    public void addMenuItem(String name, String url, String title) {
        Anchor a = new Anchor();
        a.setText(name);
        a.setHref(url);
        a.setTitle(title);
        a.addStyleName(RESOURCES.css().item());
        menuPanel.add(a);
    }

    public void clearMenuItems() {
        menuPanel.clear();
    }
}
