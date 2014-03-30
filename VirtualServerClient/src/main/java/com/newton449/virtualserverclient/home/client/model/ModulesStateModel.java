package com.newton449.virtualserverclient.home.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArray;

/**
 * A model to show some modules' state.
 * @author Steven
 */
public class ModulesStateModel extends JavaScriptObject {

    protected ModulesStateModel() {
    }

    /**
     * Returns an array of ModuleStateItem.
     *
     * @return
     */
    public native final JsArray<ModuleStateItem> getItems()/*-{ return this.items; }-*/;
}
/* example:
 {
 "items": [
 {
 "name": "Main Program",
 "description": "The main server program.",
 "state": "Running"
 },
 {
 "name": "Home",
 "description": "Provids default HTML pages.",
 "state": "Running"
 },
 {
 "name": "Installer",
 "description": "Allows others to clone your server.",
 "state": "Running"
 }
 ]
 }
 */
