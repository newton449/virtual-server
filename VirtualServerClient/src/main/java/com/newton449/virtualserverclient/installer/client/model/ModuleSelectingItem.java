package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArray;

/**
 *
 * @author Steven
 */
public class ModuleSelectingItem extends JavaScriptObject {

    protected ModuleSelectingItem() {
    }

    public native final String getName() /*-{ return this.name; }-*/;

    public native final String getDescription() /*-{ return this.description; }-*/;

    public native final JsArray<VersionState> getVersionStates() /*-{ return this.versionStates; }-*/;

}
