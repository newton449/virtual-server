package com.newton449.virtualserverclient.user.client;

/**
 * It provides a function to show errors.
 *
 * @author Steven
 */
public interface ErrorView {

    /**
     * Show the error message. Use null to clear the message.
     *
     * @param errorMessage a error message or null
     */
    void showError(String errorMessage);

}
