package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author Steven
 */
public class CloneServerConfigureRunServerPage extends Composite {

    private static CloneServerConfigureRunServerPageUiBinder uiBinder = GWT.create(CloneServerConfigureRunServerPageUiBinder.class);

    interface CloneServerConfigureRunServerPageUiBinder extends UiBinder<Widget, CloneServerConfigureRunServerPage> {
    }

    public interface Presenter {

        void onPrevious();
    }
    private Presenter presenter;

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }
    @UiField
    Button previousButton;

    public CloneServerConfigureRunServerPage() {
        initWidget(uiBinder.createAndBindUi(this));

        // actions
        previousButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onPrevious();
            }
        });
    }

    public void lockUI() {
        previousButton.setEnabled(false);
    }

    public void unlockUI() {
        previousButton.setEnabled(true);
    }
}
