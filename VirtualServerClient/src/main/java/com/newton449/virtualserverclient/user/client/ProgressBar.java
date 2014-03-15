package com.newton449.virtualserverclient.user.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.resources.client.ImageResource;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTMLPanel;

/**
 *
 * @author Steven
 */
public class ProgressBar extends Composite {

    public static final Resources RESOURCES = GWT.create(Resources.class);

    {
        RESOURCES.css().ensureInjected();
    }

    interface Resources extends ClientBundle {

        @Source("ProgressBar.png")
        ImageResource progressBarImage();

        @Source("ProgressBar.css")
        ProgressBarStyle css();

        public interface ProgressBarStyle extends CssResource {

            String outer();

            String inner();
        }
    }
    HTMLPanel outer = new HTMLPanel("");
    HTMLPanel inner = new HTMLPanel("");

    public ProgressBar() {
        outer.addStyleName(RESOURCES.css().outer());
        inner.addStyleName(RESOURCES.css().inner());
        outer.add(inner);
        initWidget(outer);
    }

    public void setProgress(float precentage) {
        if (precentage < 0) {
            this.setVisible(false);
        } else {
            this.getElement().getStyle().clearVisibility();
            inner.setWidth(((int) precentage) + "%");
        }
    }

}
