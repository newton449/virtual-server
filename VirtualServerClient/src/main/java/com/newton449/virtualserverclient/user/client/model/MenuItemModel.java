package com.newton449.virtualserverclient.user.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class MenuItemModel extends JavaScriptObject {

    protected MenuItemModel() {
    }

    public final native String getName() /*-{ return this.name; }-*/;

    public final native String getUrl() /*-{ return this.url; }-*/;
    
    public final native String getTitle() /*-{ return this.title; }-*/;

}
