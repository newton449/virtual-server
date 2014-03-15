package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.JsArray;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HTMLTable;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.installer.client.model.ModuleItem;
import com.newton449.virtualserverclient.installer.client.model.ModulesModel;
import com.newton449.virtualserverclient.installer.client.model.VersionState;

/**
 *
 * @author Steven
 */
public class ModulesTable extends FlexTable {

    private ModulesModel model;
    private boolean selectable = true;

    private void buildTable() {
        this.clear();
        // styles
        Resources.ModulesTableStyle css = Resources.INSTANCE.modulesTableStyle();
        css.ensureInjected();
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

        int versionCount = model.getVersions().length();
        for (int i = 0; i < versionCount; i++) {
            this.setText(1, i, model.getVersions().get(i));
            cellFormatter.addStyleName(1, i, css.header());
            cellFormatter.addStyleName(1, i, css.specificVersion());
        }
        this.getFlexCellFormatter().setColSpan(0, 2, versionCount);

        this.getRowFormatter().addStyleName(0, css.firstRow());
        this.getRowFormatter().addStyleName(1, css.secondRow());
        JsArray<ModuleItem> items = model.getItems();

        // set data
        for (int i = 0; i < items.length(); i++) {
            ModuleItem module = items.get(i);
            this.setText(i + 2, 0, module.getName());
            this.setText(i + 2, 1, module.getDescription());
            for (int j = 0; j < versionCount; j++) {
                VersionState versionState = module.getVersionStates().get(j);
                if (selectable) {
                    // put check boxes
                    CheckBox box = new CheckBox();
                    box.setEnabled(versionState.isEnabled());
                    box.setValue(versionState.isSelected());
                    this.setWidget(i + 2, j + 2, box);
                } else {
                    // TODO put hooks
                    if (versionState.isSelected()) {
                        this.setText(i + 2, j + 2, "SELECTED");
                    } else {
                        this.setText(i + 2, j + 2, "");
                    }
                }
            }
            this.getRowFormatter().addStyleName(i + 2, css.body());
        }
    }

    public ModulesModel refreshModel() {
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

    public ModulesModel getModel() {
        return model;
    }

    public void setModel(ModulesModel model) {
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
