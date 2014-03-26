package com.newton449.virtualserverclient.user.client;

/**
 * It allows user to reload data (retry action).
 *
 * @author Steven
 */
public interface ReloadableErrorView extends ErrorView {

    /**
     * Set whether reloading is enabled.
     *
     * @param b
     */
    void setReloadingEnabled(boolean b);

    boolean isReloadingEnabled();

    /**
     * Set a handler when user wants to reload data.
     *
     * @param reloadingHandler
     */
    void setReloadingHandler(ReloadingHandler reloadingHandler);
}
