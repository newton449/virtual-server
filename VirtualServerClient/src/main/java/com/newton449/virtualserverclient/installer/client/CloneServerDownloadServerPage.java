package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.i18n.client.NumberFormat;
import com.google.gwt.safehtml.shared.SafeUri;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.InlineHTML;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.user.client.ErrorView;
import com.newton449.virtualserverclient.user.client.ProgressBar;

/**
 *
 * @author Steven
 */
public class CloneServerDownloadServerPage extends Composite implements ErrorView {

    private static final CloneServerDownloadServerPageUiBinder uiBinder = GWT.create(CloneServerDownloadServerPageUiBinder.class);

    @Override
    public void showError(String errorMessage) {
        error.setText(errorMessage);
    }

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
    @UiField
    HTML error;
    @UiField
    ProgressBar progressBar;
    @UiField
    InlineHTML sizeLabel;

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
        nextButton.setEnabled(b);
    }

    public void setDownloadUrl(String url) {
        link.setHref(url);
    }

    public void setDownloadUrl(SafeUri uri) {
        link.setHref(uri);
    }

    public void setDownloadSize(long size) {
        String unit;
        double value;
        if (size > 1000000000) {
            unit = "GB";
            value = size / 1000000000.0;
        } else if (size > 1000000) {
            unit = "MB";
            value = size / 1000000.0;
        } else if (size > 1000) {
            unit = "KB";
            value = size / 1000.0;
        } else {
            unit = "B";
            value = size;
        }
        NumberFormat fmt = NumberFormat.getFormat("0.00");
        sizeLabel.setText(fmt.format(value) + unit);
    }

    public void lockUI() {
        previousButton.setEnabled(false);
        nextButton.setEnabled(false);
    }

    public void unlockUI() {
        previousButton.setEnabled(true);
        nextButton.setEnabled(true);
    }

    public void setProgress(float percentage) {
        progressBar.setProgress(percentage);
    }
}
