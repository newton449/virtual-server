package com.newton449.virtualserverclient.user.client;

import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestCallback;
import com.google.gwt.http.client.Response;

/**
 * It provides more specific callback for different error types, and provides
 * default messages for some errors.
 *
 * @author Steven
 */
public abstract class AbstractRequestCallback implements RequestCallback {

    private ErrorView errorView;

    /**
     * Construct an AbstractRequestCallback.
     */
    public AbstractRequestCallback() {
    }

    /**
     * Construct an AbstractRequestCallback with ErrorView. The ErrorView will
     * be used to show default error messages.
     *
     * @param errorView
     */
    public AbstractRequestCallback(ErrorView errorView) {
        this.errorView = errorView;
    }

    @Override
    public final void onResponseReceived(Request request, Response response) {
        if (response.getStatusCode() == 200) {
            onSuccess(request, response);
        } else {
            if (onErrorAny(request)) {
                onErrorResponse(request, response);
            }
        }
    }

    @Override
    public final void onError(Request request, Throwable exception) {
        if (onErrorAny(request)) {
            onErrorConnection(request, exception);
        }
    }

    /**
     * Called when a response is received and its status code is 200.
     *
     * @param request
     * @param response
     */
    public abstract void onSuccess(Request request, Response response);

    /**
     * Called when any kind of errors is gotten. It will be called before {@link #onErrorConnection(Request, Throwable)
     * } or {@link #onErrorResponse(Request, Response)
     * } is called. Returns true if the specific callback function need be
     * called. This function is useful to unlock UI.
     *
     * @param request
     * @return
     */
    public boolean onErrorAny(Request request) {
        return true;
    }

    /**
     * Called when a {@link com.google.gwt.http.client.Request} does not
     * complete normally. A
     * {@link com.google.gwt.http.client.RequestTimeoutException RequestTimeoutException}
     * is one example of the type of error that a request may encounter.
     *
     * @param request the request object which has experienced the error
     * condition, may be null if the request was never generated
     * @param exception the error that was encountered
     */
    public void onErrorConnection(Request request, Throwable exception) {
        errorView.showError("Got exception: " + exception.getMessage());
    }

    /**
     * Called when the response code is not 200.
     *
     * @param request
     * @param response
     */
    public void onErrorResponse(Request request, Response response) {
        errorView.showError("Got error response: " + response.getStatusCode() + " " + response.getText());
    }

    /**
     * Returns an ErrorView. The ErrorView will be used to show default error
     * messages.
     *
     * @return
     */
    public ErrorView getErrorView() {
        return errorView;
    }

    /**
     * Sets an ErrorView. The ErrorView will be used to show default error
     * messages.
     *
     * @param errorView
     */
    public void setErrorView(ErrorView errorView) {
        this.errorView = errorView;
    }

}
