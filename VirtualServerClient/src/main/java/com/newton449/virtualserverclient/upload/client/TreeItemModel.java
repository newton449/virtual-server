package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.JavaScriptObject;

/**
 *
 * @author Steven
 */
public class TreeItemModel extends JavaScriptObject {

    protected TreeItemModel() {
    }

    public final native int getChildSize()/*-{
     var name=Object.keys(this)[0];
     var childObject = this[name];
     if(childObject instanceof Array){
     return 0;
     }else{
     return Object.keys(childObject).length;
     }
     }-*/;

    public final native TreeItemModel getChild(int index) /*-{
     var childObject = this[Object.keys(this)[0]];
     if(childObject instanceof Array){
     return null;
     }else{
     var name = Object.keys(childObject)[index];
     var value = childObject[name];
     var ret = {};
     ret[name] = value;
     return ret;
     }
     }-*/;

    public native final String getName()/*-{ 
     return Object.keys(this)[0];
     }-*/;

    public native final boolean isLeaf()/*-{
     var childObject = this[Object.keys(this)[0]];
     if(childObject instanceof Array){
     return true;
     }else{
     return false;
     }
     }-*/;

}
