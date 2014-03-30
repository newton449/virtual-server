package com.newton449.virtualserverclient.home.client.model;

/**
 * A model to show server information.
 *
 * @author Steven
 */
public class ServerInfoModel extends ModulesStateModel {

    protected ServerInfoModel() {
    }

    /**
     * Returns the platform information of server.
     *
     * @return
     */
    public native final String getPlatformInfo()/*-{ return this.platformInfo; }-*/;

}
/*
 {
 "platformInfo": "Windows 8 v6.2 on amd64; en_US",
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
