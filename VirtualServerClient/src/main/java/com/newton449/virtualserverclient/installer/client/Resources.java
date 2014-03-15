package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.ClientBundle.Source;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.resources.client.ImageResource;

/**
 *
 * @author Steven
 */
interface Resources extends ClientBundle {

    public static final Resources INSTANCE = GWT.create(Resources.class);

    @Source("step1.png")
    ImageResource step1();

    @Source("step2.png")
    ImageResource step2();

    @Source("step3.png")
    ImageResource step3();

    @Source("step4.png")
    ImageResource step4();

    @Source("ModulesTable.css")
    ModulesTableStyle modulesTableStyle();

    public interface ModulesTableStyle extends CssResource {

        String table();
        
        String header();

        String firstRow();

        String secondRow();

        String name();

        String description();

        String platforms();

        String specificVersion();

        String body();
    }
}
