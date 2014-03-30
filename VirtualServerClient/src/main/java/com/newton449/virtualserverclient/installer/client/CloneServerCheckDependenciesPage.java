package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArrayString;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.installer.client.model.CheckingDependenciesModel;
import com.newton449.virtualserverclient.installer.client.model.CreatingServerModel;
import com.newton449.virtualserverclient.installer.client.model.ModulesSelectingModel;
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

        void onPrevious(ModulesSelectingModel model);

        void onNext(CreatingServerModel model);
    }
    private Presenter presenter;

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    @UiField
    ModulesSelectingTable table;
    @UiField
    Button previousButton;
    @UiField
    Button nextButton;
    @UiField
    HTML error;
    @UiField
    ListBox compBox;
    CheckingDependenciesModel model;

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
                CreatingServerModel nextModel = (CreatingServerModel) JavaScriptObject.createObject().cast();
                nextModel.setModules(model.getModules());
                nextModel.setPackType(compBox.getValue(compBox.getSelectedIndex()));
                presenter.onNext(nextModel);
            }
        });
    }

    public void setModel(CheckingDependenciesModel model) {
        this.model = model;
        table.setSelectable(false);
        table.setModel(model.getModules());
        // list box
        compBox.clear();
        JsArrayString compressedTypeList = model.getPackTypes();
        for (int i = 0; i < compressedTypeList.length(); i++) {
            compBox.addItem(compressedTypeList.get(i));
        }
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
