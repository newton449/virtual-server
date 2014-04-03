package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArrayString;

/**
 * A model contains dependencies-solved modules and supported pack types.
 *
 * @author Steven
 */
public class CheckingDependenciesModel extends JavaScriptObject {

    protected CheckingDependenciesModel() {
    }

    /**
     * Returns an array of string for pack types such as zip and tar.
     *
     * @return
     */
    public native final JsArrayString getPackTypes() /*-{ return this.packTypes; }-*/;

    public native final void setPackTypes(JsArrayString types) /*-{ this.packTypes = types; }-*/;

    /**
     * Return selected modules.
     *
     * @return
     */
    public native final ModulesSelectingModel getModules() /*-{ return this.modules; }-*/;

    public native final void setModules(ModulesSelectingModel model) /*-{ this.modules = model; }-*/;

}
/*


 */
