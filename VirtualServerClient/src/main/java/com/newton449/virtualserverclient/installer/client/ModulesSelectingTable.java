package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.JsArray;
import com.google.gwt.core.client.JsArrayString;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HTMLTable;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.installer.client.model.ModuleSelectingItem;
import com.newton449.virtualserverclient.installer.client.model.ModulesSelectingModel;
import com.newton449.virtualserverclient.installer.client.model.VersionState;
import com.newton449.virtualserverclient.user.client.JsonAssertion;

/**
 *
 * @author Steven
 */
public class ModulesSelectingTable extends FlexTable {

    private ModulesSelectingModel model;
    private boolean selectable = true;

    private void buildTable() {
        this.clear();
        // styles
        Resources.ModulesTableStyle css = Resources.Utils.INSTANCE.modulesTableStyle();
        this.addStyleName(css.table());
        HTMLTable.CellFormatter cellFormatter = this.getCellFormatter();

        // build header
        // build "name"
        this.getFlexCellFormatter().setRowSpan(0, 0, 2);
        this.setText(0, 0, "Name");
        cellFormatter.addStyleName(0, 0, css.header());
        cellFormatter.addStyleName(0, 0, css.name());

        // build "description"
        this.getFlexCellFormatter().setRowSpan(0, 1, 2);
        this.setText(0, 1, "Description");
        cellFormatter.addStyleName(0, 1, css.header());
        cellFormatter.addStyleName(0, 1, css.description());

        // build platform
        this.setText(0, 2, "Platforms");
        cellFormatter.addStyleName(0, 2, css.header());
        cellFormatter.addStyleName(0, 2, css.platforms());

        JsArrayString versions = model.getVersions();
        JsonAssertion.propertyNotNull(versions, "versions");
        int versionCount = versions.length();
        for (int i = 0; i < versionCount; i++) {
            this.setText(1, i, versions.get(i));
            cellFormatter.addStyleName(1, i, css.header());
            cellFormatter.addStyleName(1, i, css.specificVersion());
        }
        this.getFlexCellFormatter().setColSpan(0, 2, versionCount);

        this.getRowFormatter().addStyleName(0, css.firstRow());
        this.getRowFormatter().addStyleName(1, css.secondRow());
        JsArray<ModuleSelectingItem> items = model.getItems();
        JsonAssertion.propertyNotNull(items, "items");

        // set data
        for (int i = 0; i < items.length(); i++) {
            ModuleSelectingItem module = items.get(i);
            this.setText(i + 2, 0, module.getName());
            this.setText(i + 2, 1, module.getDescription());
            JsArray<VersionState> versionStates = module.getVersionStates();
            JsonAssertion.propertyNotNull(versionStates, "versionStates");
            for (int j = 0; j < versionCount; j++) {
                VersionState versionState = versionStates.get(j);
                this.getCellFormatter().addStyleName(i + 2, j + 2, css.correctCell());
                if (selectable) {
                    // put check boxes, when it is selectable or selected
                    if (versionState.isEnabled() || versionState.isSelected()) {
                        CheckBox box = new CheckBox();
                        box.addStyleName(css.box());
                        box.setEnabled(versionState.isEnabled());
                        box.setValue(versionState.isSelected());
                        this.setWidget(i + 2, j + 2, box);
                    }
                } else {
                    // put hooks
                    if (versionState.isSelected()) {
                        Image image = new Image(Resources.Utils.INSTANCE.correct());
                        image.addStyleName(css.correctImage());
                        this.setWidget(i + 2, j + 2, image);
                    } else {
                        this.setText(i + 2, j + 2, "");
                    }
                }
            }
            this.getRowFormatter().addStyleName(i + 2, css.body());
        }
    }

    public ModulesSelectingModel refreshModel() {
        if (selectable) {
            // update verion states according to check boxes
            for (int i = 0; i < model.getItems().length(); i++) {
                for (int j = 0; j < model.getItems().get(i).getVersionStates().length(); j++) {
                    // get the check box
                    Widget w = this.getWidget(i + 2, j + 2);
                    if (w instanceof CheckBox) {
                        // set selected
                        CheckBox cb = (CheckBox) w;
                        model.getItems().get(i).getVersionStates().get(j).setSelected(cb.getValue());
                    }
                }
            }
        }
        return model;
    }

    public ModulesSelectingModel getModel() {
        return model;
    }

    public void setModel(ModulesSelectingModel model) {
        this.model = model;
        buildTable();
    }

    public boolean isSelectable() {
        return selectable;
    }

    public void setSelectable(boolean selectable) {
        this.selectable = selectable;
    }
}
