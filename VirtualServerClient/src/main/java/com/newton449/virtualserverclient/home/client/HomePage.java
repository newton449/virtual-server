package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.dom.client.SpanElement;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.home.client.model.ServerInfoModel;

/**
 * A page which is the index of the whole web site. It contains an introduction
 * of Virtual Server, a platform state, and a table of modules.
 *
 * @author Steven
 */
public class HomePage extends Composite {

    private static final HomePageUiBinder uiBinder = GWT.create(HomePageUiBinder.class);

    interface HomePageUiBinder extends UiBinder<Widget, HomePage> {
    }

    @UiField
    SpanElement platformInfo;
    @UiField
    ModulesStateTable table;

    public HomePage() {
        initWidget(uiBinder.createAndBindUi(this));
    }

    public void setModel(ServerInfoModel model) {
        table.setModel(model);
        platformInfo.setInnerText(model.getPlatformInfo());
    }
}
