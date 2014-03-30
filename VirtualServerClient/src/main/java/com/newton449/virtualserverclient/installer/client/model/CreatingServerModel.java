package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;

/**
 * A model for creating a server file.
 *
 * @author Steven
 */
public class CreatingServerModel extends JavaScriptObject {

    protected CreatingServerModel() {
    }

    /**
     * Returns the file type.
     *
     * @return
     */
    public native final String getPackType() /*-{ return this.packType }-*/;

    public native final void setPackType(String type) /*-{ this.packType = type; }-*/;

    /**
     * Returns selected modules.
     *
     * @return
     */
    public native final ModulesSelectingModel getModules() /*-{ return this.modules; }-*/;

    public native final void setModules(ModulesSelectingModel model)/*-{ this.modules = model; }-*/;

}
/*
 {
 "packType": "zip",
 "modules": {
 "versions": [
 "Windows",
 "Linux x86",
 "Linux x64"
 ],
 "items": [
 {
 "name": "Main Program",
 "description": "The main server program.",
 "versionStates": [
 {
 "enabled": false,
 "selected": true
 },
 {
 "enabled": false,
 "selected": false
 },
 {
 "enabled": false,
 "selected": false
 }
 ]
 },
 {
 "name": "Installer",
 "description": "Allows others to clone your server.",
 "versionStates": [
 {
 "enabled": true,
 "selected": true
 },
 {
 "enabled": true,
 "selected": false
 },
 {
 "enabled": true,
 "selected": false
 }
 ]
 },
 {
 "name": "File Manager",
 "description": "Supports uploading and downloading files.",
 "versionStates": [
 {
 "enabled": true,
 "selected": true
 },
 {
 "enabled": false,
 "selected": false
 },
 {
 "enabled": false,
 "selected": false
 }
 ]
 }
 ]
 }
 }
 */
