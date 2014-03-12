package com.newton449.virtualserverclient.user.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.logical.shared.ResizeEvent;
import com.google.gwt.event.logical.shared.ResizeHandler;
import com.google.gwt.event.shared.HandlerRegistration;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.Window.ScrollEvent;
import com.google.gwt.user.client.Window.ScrollHandler;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.InlineLabel;
import com.google.gwt.user.client.ui.PopupPanel;

public class GlobalMessagePanel extends PopupPanel implements ReloadableErrorView {

    private final InlineLabel label = new InlineLabel("This is message label.");
    private final InlineLabel reloadLabel;
    private final InlineLabel closeLabel;
    private HandlerRegistration resizeReg;
    private HandlerRegistration scrollReg;
    private ReloadingHandler reloadingHandler;
    private boolean reloadingEnabled = true;
    private int loadedCount = 1;

    @Override
    public void setReloadingEnabled(boolean b) {
        reloadingEnabled = b;
        reloadLabel.setVisible(b);
    }

    @Override
    public boolean isReloadingEnabled() {
        return reloadingEnabled;
    }

    @Override
    public void setReloadingHandler(ReloadingHandler reloadingHandler) {
        this.reloadingHandler = reloadingHandler;
    }

    interface GlobalMessagePanelResources extends ClientBundle {

        @Source("GlobalMessagePanel.css")
        MyCss css();

        interface MyCss extends CssResource {

            String panel();

            String message();

            String error();

            String close();

            String reload();

        }
    }

    private static final GlobalMessagePanelResources RESOURCES = GWT
            .create(GlobalMessagePanelResources.class);

    {
        RESOURCES.css().ensureInjected();
    }

    public GlobalMessagePanel() {
        this.setStyleName(RESOURCES.css().panel());
        reloadLabel = new InlineLabel("Reload");
        closeLabel = new InlineLabel("Close");
        FlowPanel panel = new FlowPanel();
        panel.add(label);
        panel.add(reloadLabel);
        panel.add(closeLabel);
        reloadLabel.setStyleName(RESOURCES.css().reload());
        reloadLabel.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                ReloadingHandler reloadingHandler = GlobalMessagePanel.this.reloadingHandler;
                if (reloadingHandler != null) {
                    clearMessage();
                    loadedCount++;
                    reloadingHandler.onReload();
                }

            }
        });
        closeLabel.setStyleName(RESOURCES.css().close());
        closeLabel.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                clearMessage();
            }
        });
        this.setWidget(panel);
    }

    /**
     * reset the popupPanel's position.
     * <p>
     * This method will try to put the popupPanel in the center of the
     * ClientFrame's CENTER panel instead of the center of Window. If the
     * popupPanel is too wide to put in the center of the CENTER panel, it will
     * be put "margin-left:10%" to the Window's left border. And the maximal
     * width is 80% of Window, which means the panel is "margin-left:10%" and
     * "margin-right:10%" and it is now in the center of Window.
     * </p>
     */
    private void resetPosition() {
        // Calculate by panel's width, Window's width, eastPanel's width and
        // panel's left margin
        int offsetWidth = super.getOffsetWidth();
        // 0.1 is because the left margin is 10%
        int left = (Window.getClientWidth() - offsetWidth - 230) / 2
                - (int) (Window.getClientWidth() * 0.1);
        if (left < 0) {
            left = 0;
        }
        left += Window.getScrollLeft();
        int top = (int) (Window.getClientHeight() * 0.15)
                + Window.getScrollTop();
        super.setPopupPosition(left, top);
    }

    @Override
    public void show() {
        if (super.isShowing()) {
            return;
        }
        super.show();
        updateHandler(true);
    }

    @Override
    public void hide(boolean autoClosed) {
        if (!isShowing()) {
            return;
        }
        super.hide(autoClosed);
        updateHandler(false);
    }

    private void updateHandler(boolean showing) {
        if (resizeReg != null) {
            resizeReg.removeHandler();
            resizeReg = null;
        }
        if (scrollReg != null) {
            scrollReg.removeHandler();
            scrollReg = null;
        }
        if (showing) {
            resizeReg = Window.addResizeHandler(new ResizeHandler() {

                @Override
                public void onResize(ResizeEvent event) {
                    resetPosition();

                }
            });

            scrollReg = Window.addWindowScrollHandler(new ScrollHandler() {

                @Override
                public void onWindowScroll(ScrollEvent event) {
                    resetPosition();
                }
            });
        }
    }

    private void _show() {
        if (!super.isShowing()) {
            // whether show reloadLabel
            reloadLabel.setVisible(reloadingHandler != null);

            // show
            super.setPopupPositionAndShow(new PositionCallback() {

                @Override
                public void setPosition(int offsetWidth, int offsetHeight) {
                    resetPosition();
                }
            });
        }
    }

    @Override
    public void showError(String error) {
        if (error == null) {
            clearMessage();
        } else {
            label.setStyleName(RESOURCES.css().message());
            // show the loaded count so that users can know it worked.
            if (loadedCount > 1) {
                label.setText("(#" + loadedCount + ") " + error);
            } else {
                label.setText(error);
            }
            _show();
        }
    }

    public void clearMessage() {
        label.setText("");
        hide();
    }

}
