package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArray;
import com.google.gwt.core.client.JsArrayString;

/**
 *
 * @author Steven
 */
public class ModulesModel extends JavaScriptObject {

    protected ModulesModel() {
    }

    public native final JsArray<ModuleItem> getItems() /*-{ return this.modules; }-*/;

    public native final JsArrayString getVersions() /*-{ return this.versions; }-*/;
}
