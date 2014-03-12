package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.installer.client.model.ModulesModel;
import com.newton449.virtualserverclient.user.client.ErrorView;

/**
 *
 * @author Steven
 */
public class CloneServerCheckDependenciesPage extends Composite implements ErrorView {

    private static final CloneServerCheckDependenciesPageUiBinder uiBinder = GWT.create(CloneServerCheckDependenciesPageUiBinder.class);

    interface CloneServerCheckDependenciesPageUiBinder extends UiBinder<Widget, CloneServerCheckDependenciesPage> {
    }

    public interface Presenter {

        void onPrevious(ModulesModel model);

        void onNext(ModulesModel model);
    }
    private Presenter presenter;

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    @UiField
    ModulesTable table;
    @UiField
    Button previousButton;
    @UiField
    Button nextButton;
    @UiField
    HTML error;

    public CloneServerCheckDependenciesPage() {
        initWidget(uiBinder.createAndBindUi(this));
        previousButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onPrevious(table.getModel());
            }
        });
        nextButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onNext(table.getModel());
            }
        });
    }

    public void setModel(ModulesModel model) {
        table.setSelectable(false);
        table.setModel(model);
    }

    @Override
    public void showError(String errorMessage) {
        error.setText(errorMessage);
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
