package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.ClientBundle.Source;
import com.google.gwt.resources.client.CssResource;

/**
 *
 * @author Steven
 */
interface Resources extends ClientBundle {

    public static class Utils {

        public static final Resources INSTANCE = GWT.create(Resources.class);

        static {
            INSTANCE.modulesTableStyle().ensureInjected();
        }
    }

    @Source("ModulesStateTable.css")
    ModulesTableStyle modulesTableStyle();

    public interface ModulesTableStyle extends CssResource {

        String table();

        String header();

        String firstRow();

        String name();

        String description();

        String state();

        String body();

    }
}
