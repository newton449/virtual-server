package com.newton449.virtualserverclient.home.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 * A model to show a module's state.
 *
 * @author Steven
 */
public class ModuleStateItem extends JavaScriptObject {

    protected ModuleStateItem() {
    }

    /**
     * Returns the name of module.
     *
     * @return
     */
    public native final String getName() /*-{ return this.name; }-*/;

    /**
     * Returns the description of module.
     *
     * @return
     */
    public native final String getDescription() /*-{ return this.description; }-*/;

    /**
     * Returns the state of module.
     *
     * @return
     */
    public native final String getState()/*-{ return this.state; }-*/;
}
