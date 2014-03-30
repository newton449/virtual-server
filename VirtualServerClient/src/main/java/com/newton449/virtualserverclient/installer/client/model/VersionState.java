package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class VersionState extends JavaScriptObject {

    protected VersionState() {
    }

    public native final boolean isEnabled() /*-{ return this.enabled; }-*/;

    public native final boolean isSelected() /*-{ return this.selected; }-*/;

    public native final void setSelected(boolean b) /*-{ this.selected = b; }-*/;
}
