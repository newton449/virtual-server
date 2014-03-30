package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class FileKeyModel extends JavaScriptObject {

    protected FileKeyModel() {
    }

    /**
     * Returns a string key to present a file.
     *
     * @return
     */
    public native final String getFileKey() /*-{ return this.fileKey; }-*/;
}
/*
{
    "fileKey": "..."
}
*/