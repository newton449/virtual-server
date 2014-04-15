package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class TreeViewModel extends JavaScriptObject {

    protected TreeViewModel() {
    }

    public final TreeItemModel getRoot() {
        TreeItemModel ret = this.cast();
        return ret;
    }
}
