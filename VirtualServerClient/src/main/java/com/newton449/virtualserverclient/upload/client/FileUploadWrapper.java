package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.ClientBundle.Source;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FileUpload;
import com.google.gwt.user.client.ui.FlowPanel;

/**
 *
 * @author Steven
 */
public class FileUploadWrapper extends Composite {

    interface Resources extends ClientBundle {

        @Source("FileUploadWrapper.css")
        Style css();

        public interface Style extends CssResource {

            String container();

            String fileUpload();

            String delete();
        }
    }
    private static final Resources RESOURCES = GWT.create(Resources.class);

    static {
        RESOURCES.css().ensureInjected();
    }

    public interface Presenter {

        void onDelete(FileUploadWrapper wrapper);
    }
    private Presenter presenter;

    private FileUpload fileUpload = new FileUpload();
    private Button delete = new Button("X");

    public FileUploadWrapper() {
        // build basic structure
        FlowPanel container = new FlowPanel();
        initWidget(container);
        container.addStyleName(RESOURCES.css().container());
        fileUpload.addStyleName(RESOURCES.css().fileUpload());
        fileUpload.setName("file");
        container.add(fileUpload);
        delete.addStyleName(RESOURCES.css().delete());
        container.add(delete);
        delete.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                presenter.onDelete(FileUploadWrapper.this);
            }
        });

        // the widget cannot be deleted if no file is choosen.
        delete.setVisible(false);
        fileUpload.addChangeHandler(new ChangeHandler() {

            @Override
            public void onChange(ChangeEvent event) {
                if (fileUpload.getFilename() != null && !fileUpload.getFilename().isEmpty()) {
                    delete.setVisible(true);
                } else {
                    delete.setVisible(false);
                }
            }
        });
    }

    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    public FileUpload getFileUpload() {
        return fileUpload;
    }
}
