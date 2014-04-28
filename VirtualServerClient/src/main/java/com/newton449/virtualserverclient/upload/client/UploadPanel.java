package com.newton449.virtualserverclient.upload.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.core.client.JsArrayString;
import com.google.gwt.core.client.JsonUtils;
import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.logical.shared.SelectionEvent;
import com.google.gwt.event.logical.shared.SelectionHandler;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.AcceptsOneWidget;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.FormPanel;
import com.google.gwt.user.client.ui.Hidden;
import com.google.gwt.user.client.ui.InlineLabel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Tree;
import com.google.gwt.user.client.ui.TreeItem;
import com.google.gwt.user.client.ui.Widget;
import com.newton449.virtualserverclient.user.client.AbstractRequestCallback;
import com.newton449.virtualserverclient.user.client.GlobalMessagePanel;
import com.newton449.virtualserverclient.user.client.RequestSender;

/**
 *
 * @author Steven
 */
public class UploadPanel extends Composite {

    private static UploadPanelUiBinder uiBinder = GWT.create(UploadPanelUiBinder.class);

    interface UploadPanelUiBinder extends UiBinder<Widget, UploadPanel> {
    }

    @UiField
    FormPanel form;
    @UiField
    Button submitButton;
    @UiField
    FlowPanel uploadingFilesPanel;
    @UiField
    Tree dirTree;
    @UiField
    InlineLabel pathLabel;
    @UiField
    Hidden pathHidden;
    @UiField
    FlowPanel currentFilesPanel;
    @UiField
    InlineLabel versionLabel;
    FileUploadWrapper lastUploadWrapper;
    AcceptsOneWidget container;

    public UploadPanel() {
        initWidget(uiBinder.createAndBindUi(this));

        // add an initial FileUpload to the uploadingFilesPanel
        if (uploadingFilesPanel.getWidgetCount() == 0) {
            lastUploadWrapper = new FileUploadWrapper();
            uploadingFilesPanel.add(lastUploadWrapper);
        } else {
            lastUploadWrapper = (FileUploadWrapper) uploadingFilesPanel.getWidget(uploadingFilesPanel.getWidgetCount() - 1);
        }
        // if a file is choosed or changed, refresh file panel
        lastUploadWrapper.getFileUpload().addChangeHandler(new ChangeHandler() {

            @Override
            public void onChange(ChangeEvent event) {
                refreshFilePanel();
            }
        });
        // add remove listener
        lastUploadWrapper.setPresenter(new FileUploadWrapper.Presenter() {

            @Override
            public void onDelete(FileUploadWrapper wrapper) {
                uploadingFilesPanel.remove(wrapper);
            }
        });
        // submit form
        submitButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                pathHidden.setValue(pathLabel.getText());
                form.submit();
            }
        });

        // submit complete
        form.addSubmitCompleteHandler(new FormPanel.SubmitCompleteHandler() {

            @Override
            public void onSubmitComplete(FormPanel.SubmitCompleteEvent event) {
                Window.alert(event.getResults());
            }
        });

        // tree selection
        dirTree.addSelectionHandler(new SelectionHandler<TreeItem>() {

            @Override
            public void onSelection(SelectionEvent<TreeItem> event) {
                onSelect(event.getSelectedItem());
            }
        });
    }

    public void start(AcceptsOneWidget container) {
        this.container = container;
        // load tree view
        loadTreeView();

    }

    private void onSelect(TreeItem item) {
        if (item.getText().startsWith("version")) {
            // set version
            versionLabel.setText(item.getText());
            onSelectWithoutVersion(item.getParentItem());

            // set files
            currentFilesPanel.clear();
            JsArrayString files = ((TreeItemModel) item.getUserObject()).getFiles();
            if (files == null || files.length() == 0) {
                currentFilesPanel.add(new Label("No file."));
            } else {
                for (int i = 0; i < files.length(); i++) {
                    currentFilesPanel.add(new Label(files.get(i)));
                }
            }
        } else {
            versionLabel.setText("NONE");
            onSelectWithoutVersion(item);

            // set files
            currentFilesPanel.clear();
            currentFilesPanel.add(new Label("No file."));
        }

    }

    private void onSelectWithoutVersion(TreeItem item) {
        // find full path
        String fullPath = "/" + item.getText();
        TreeItem parent = item.getParentItem();
        while (parent != null) {
            fullPath = "/" + parent.getText() + fullPath;
            parent = parent.getParentItem();
        }
        pathLabel.setText(fullPath);
    }

    private void loadTreeView() {
        RequestSender sender = new RequestSender(RequestBuilder.GET, "/upload/tree_view");
        final GlobalMessagePanel errorPanel = new GlobalMessagePanel();
        sender.setErrorHandler(errorPanel);
        sender.setRequestData(null);
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                // parse response
                String text = response.getText();
                TreeViewModel model;
                try {
                    model = JsonUtils.safeEval(text);
                } catch (IllegalArgumentException ex) {
                    errorPanel.showError("Failed to get final modules. Got :" + (text.length() > 40 ? text.substring(0, 40) + "..." : text));
                    return;
                }
                try {
                    refreshTreeView(model);
                    container.setWidget(UploadPanel.this);
                } catch (Exception ex) {
                    errorPanel.showError("System Bug: " + ex.getMessage());
                }
            }
        });
        sender.send();
    }

    void refreshFilePanel() {
        // check all uploads except for the last one
        for (int i = 0; i < uploadingFilesPanel.getWidgetCount() - 1; i++) {
            Widget w = uploadingFilesPanel.getWidget(i);
            if (w instanceof FileUploadWrapper) {
                FileUploadWrapper wrapper = (FileUploadWrapper) w;
                if (wrapper.getFileUpload().getFilename() == null || wrapper.getFileUpload().getFilename().isEmpty()) {
                    // no file is selected. remove it.
                    uploadingFilesPanel.remove(i);
                    i--;
                }
            }
        }
        // check the last upload
        if (lastUploadWrapper.getFileUpload().getFilename() != null && !lastUploadWrapper.getFileUpload().getFilename().isEmpty()) {
            // add a new upload
            lastUploadWrapper = new FileUploadWrapper();
            lastUploadWrapper.getFileUpload().addChangeHandler(new ChangeHandler() {

                @Override
                public void onChange(ChangeEvent event) {
                    refreshFilePanel();
                }
            });
            lastUploadWrapper.setPresenter(new FileUploadWrapper.Presenter() {

                @Override
                public void onDelete(FileUploadWrapper wrapper) {
                    uploadingFilesPanel.remove(wrapper);
                }
            });
            uploadingFilesPanel.add(lastUploadWrapper);
        }
    }

    void refreshTreeView(TreeViewModel model) {
        TreeItem root = buildTreeItem(model.getRoot());
        dirTree.clear();
        dirTree.addItem(root);
        // set path
        pathLabel.setText("/" + root.getText());
    }

    private TreeItem buildTreeItem(TreeItemModel model) {
        if (model == null) {
            return null;
        }
        TreeItem ret = new TreeItem();
        // name
        ret.setText(model.getName());
        // data
        ret.setUserObject(model);
        // child
        if (!model.isLeaf()) {
            int size = model.getChildSize();
            for (int i = 0; i < size; i++) {
                ret.addItem(buildTreeItem(model.getChild(i)));
            }
            ret.setState(true);
        }
        return ret;
    }
}
