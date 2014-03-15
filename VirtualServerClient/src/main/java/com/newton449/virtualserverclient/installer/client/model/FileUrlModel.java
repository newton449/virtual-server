package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class FileUrlModel extends JavaScriptObject {

    protected FileUrlModel() {
    }

    /**
     * Returns file URL if file is created.
     *
     * @return
     */
    public native final String getFileUrl() /*-{ return this.fileUrl; }-*/;

    /**
     * Returns file size in bytes if file is created.
     *
     * @return
     */
    public native final int getFileSize() /*-{ return this.fileSize; }-*/;

    /**
     * Returns the file creating percentage. Returns 100 if file is created.
     * Returns -1 if it is not supported.
     *
     * @return
     */
    public native final float getPercentage() /*-{ return this.percentage; }-*/;

    /**
     * Returns the waiting time in millisecond to send next checking request.
     * The client will send checking request again and again to check the
     * creation of file. Use this function to control time between two requests.
     *
     * @return
     */
    public native final int getWaitingMillisecond() /*-{ return this.waitingMillisecond; }-*/;

}
