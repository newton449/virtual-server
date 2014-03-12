package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.dom.client.DivElement;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.safehtml.shared.SafeUri;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author Steven
 */
public class CloneServerDownloadServerPage extends Composite {

    private static CloneServerDownloadServerPageUiBinder uiBinder = GWT.create(CloneServerDownloadServerPageUiBinder.class);

    interface CloneServerDownloadServerPageUiBinder extends UiBinder<Widget, CloneServerDownloadServerPage> {
    }

    public interface Presenter {

        void onPrevious();

        void onNext();
    }
    private Presenter presenter;

    @UiField
    Button previousButton;
    @UiField
    Button nextButton;
    @UiField
    Anchor link;
    @UiField
    HTMLPanel waitingPanel;
    @UiField
    HTMLPanel finishedPanel;

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    public CloneServerDownloadServerPage() {
        initWidget(uiBinder.createAndBindUi(this));

        // set actions
        previousButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onPrevious();
            }
        });
        nextButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onNext();
            }
        });
    }

    public boolean isDownloadable() {
        return finishedPanel.isVisible();
    }

    public void setDownloadable(boolean b) {
        waitingPanel.setVisible(!b);
        finishedPanel.setVisible(b);
    }

    public void setDownloadUrl(String url) {
        link.setHref(url);
    }

    public void setDownloadUrl(SafeUri uri) {
        link.setHref(uri);
    }

    public void lockUI() {
        previousButton.setEnabled(false);
        nextButton.setEnabled(false);
    }

    public void unlockUI() {
        previousButton.setEnabled(true);
        nextButton.setEnabled(true);
    }
}
