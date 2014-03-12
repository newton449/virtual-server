package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.installer.client.model.ModulesModel;
import com.newton449.virtualserverclient.user.client.ErrorView;

/**
 *
 * @author Steven
 */
public class CloneServerChooseModulesPage extends Composite implements ErrorView {

    private static CloneServerChooseModulesPageUiBinder uiBinder = GWT.create(CloneServerChooseModulesPageUiBinder.class);

    interface CloneServerChooseModulesPageUiBinder extends UiBinder<Widget, CloneServerChooseModulesPage> {
    }

    public interface Presenter {

        void onNext(ModulesModel model);
    }
    private Presenter presenter;

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    @UiField
    ModulesTable table;
    @UiField
    Button checkAllButton;
    @UiField
    Button uncheckAllButton;
    @UiField
    HTML error;
    @UiField
    Button nextButton;

    public CloneServerChooseModulesPage() {
        initWidget(uiBinder.createAndBindUi(this));

        // set handler
        checkAllButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                // set all enabled check boxes as true
                for (int row = 2; row < table.getRowCount(); row++) {
                    for (int column = 2; column < table.getCellCount(row); column++) {
                        Widget w = table.getWidget(row, column);
                        if (w instanceof CheckBox) {
                            CheckBox cb = (CheckBox) w;
                            if (cb.isEnabled()) {
                                cb.setValue(true);
                            }
                        }
                    }
                }
            }
        });

        uncheckAllButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                // set all enabled check boxes as false
                for (int row = 2; row < table.getRowCount(); row++) {
                    for (int column = 2; column < table.getCellCount(row); column++) {
                        Widget w = table.getWidget(row, column);
                        if (w instanceof CheckBox) {
                            CheckBox cb = (CheckBox) w;
                            if (cb.isEnabled()) {
                                cb.setValue(false);
                            }
                        }
                    }
                }
            }
        });

        nextButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onNext(table.refreshModel());
            }
        });
    }

    public void setModel(ModulesModel model) {
        table.setModel(model);
    }

    @Override
    public void showError(String errorMessage) {
        error.setText(errorMessage);
    }

    public void lockUI() {
        nextButton.setEnabled(false);
    }

    public void unlockUI() {
        nextButton.setEnabled(true);
    }

}
