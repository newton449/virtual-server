package com.newton449.virtualserverclient.installer.client.model;

import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.core.client.JsArray;
import com.google.gwt.core.client.JsArrayString;

/**
 *
 * @author Steven
 */
public class ModulesSelectingModel extends JavaScriptObject {

    protected ModulesSelectingModel() {
    }
    
    public native final JsArrayString getVersions() /*-{ return this.versions; }-*/;

    public native final JsArray<ModuleSelectingItem> getItems() /*-{ return this.items; }-*/;

}
/* example:
{
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
*/