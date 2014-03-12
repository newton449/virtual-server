package com.newton449.virtualserverclient.user.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArray;

/**
 *
 * @author Steven
 */
public class InitializationModel extends JavaScriptObject {

    protected InitializationModel() {
    }

    public final native JsArray<MenuItemModel> getMenu() /*-{ return this.menu; }-*/;
}
