package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.JsArray;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HTMLTable;
import com.newton449.virtualserverclient.home.client.model.ModulesStateModel;
import com.newton449.virtualserverclient.home.client.model.ModuleStateItem;

/**
 * A table to show {@link ModulesStateModel}. It has three columns: Name,
 * Description, and State.
 *
 * @author Steven
 */
public class ModulesStateTable extends FlexTable {

    private ModulesStateModel model;

    public ModulesStateTable() {
    }

    private void buildTable() {
        this.clear();
        // styles
        Resources.ModulesTableStyle css = Resources.Utils.INSTANCE.modulesTableStyle();
        this.addStyleName(css.table());
        HTMLTable.CellFormatter cellFormatter = this.getCellFormatter();

        // build header
        // build "name"
        this.setText(0, 0, "Name");
        cellFormatter.addStyleName(0, 0, css.header());
        cellFormatter.addStyleName(0, 0, css.name());

        // build "description"
        this.setText(0, 1, "Description");
        cellFormatter.addStyleName(0, 1, css.header());
        cellFormatter.addStyleName(0, 1, css.description());

        // build state
        this.setText(0, 2, "State");
        cellFormatter.addStyleName(0, 2, css.header());
        cellFormatter.addStyleName(0, 2, css.state());

        this.getRowFormatter().addStyleName(0, css.firstRow());
        JsArray<ModuleStateItem> items = model.getItems();

        // set data
        for (int i = 0; i < items.length(); i++) {
            ModuleStateItem item = items.get(i);
            this.setText(i + 1, 0, item.getName());
            this.setText(i + 1, 1, item.getDescription());
            this.setText(i + 1, 2, item.getState());
            this.getRowFormatter().addStyleName(i + 1, css.body());
        }
    }

    public ModulesStateModel getModel() {
        return model;
    }

    public void setModel(ModulesStateModel model) {
        this.model = model;
        buildTable();
    }

}
