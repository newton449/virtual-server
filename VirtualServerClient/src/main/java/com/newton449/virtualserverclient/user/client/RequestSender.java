package com.newton449.virtualserverclient.user.client;

import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.RequestBuilder.Method;
import com.google.gwt.http.client.RequestCallback;
import com.google.gwt.http.client.RequestException;

/**
 *
 * @author Steven
 */
public class RequestSender {

    private RequestBuilder builder;
    private ErrorView errorView;
    AbstractRequestCallback abstractRequestCallback;

    public RequestSender(Method httpMethod, String url) {
        builder = new RequestBuilder(httpMethod, url);
    }

    public RequestCallback getCallback() {
        return builder.getCallback();
    }

    public String getHeader(String header) {
        return builder.getHeader(header);
    }

    public String getHTTPMethod() {
        return builder.getHTTPMethod();
    }

    public String getPassword() {
        return builder.getPassword();
    }

    public String getRequestData() {
        return builder.getRequestData();
    }

    public int getTimeoutMillis() {
        return builder.getTimeoutMillis();
    }

    public String getUrl() {
        return builder.getUrl();
    }

    public String getUser() {
        return builder.getUser();
    }

    public Request send() {
        try {
            return builder.send();
        } catch (RequestException ex) {
            builder.getCallback().onError(null, ex);
            return null;
        }
    }

//    public Request sendRequest(String requestData, final RequestCallback callback) {
//        try {
//            return builder.sendRequest(requestData, callback);
//        } catch (RequestException ex) {
//            callback.onError(null, ex);
//            return null;
//        }
//    }
    public void setCallback(RequestCallback callback) {
        builder.setCallback(callback);
        if (callback instanceof AbstractRequestCallback) {
            abstractRequestCallback = (AbstractRequestCallback) callback;
            abstractRequestCallback.setErrorView(errorView);
        } else {
            abstractRequestCallback = null;
        }
    }

    public void setHeader(String header, String value) {
        builder.setHeader(header, value);
    }

    public void setPassword(String password) {
        builder.setPassword(password);
    }

    public void setRequestData(String requestData) {
        builder.setRequestData(requestData);
    }

    public void setTimeoutMillis(int timeoutMillis) {
        builder.setTimeoutMillis(timeoutMillis);
    }

    public void setUser(String user) {
        builder.setUser(user);
    }

    public void setIncludeCredentials(boolean includeCredentials) {
        builder.setIncludeCredentials(includeCredentials);
    }

    /**
     * @return the errorView
     */
    public ErrorView getErrorHandler() {
        return errorView;
    }

    /**
     * @param errorView the errorView to set
     */
    public void setErrorHandler(ErrorView errorView) {
        this.errorView = errorView;
        if (errorView instanceof ReloadableErrorView) {
            ((ReloadableErrorView) errorView).setReloadingHandler(new ReloadingHandler() {

                @Override
                public void onReload() {
                    send();
                }
            });
        }
        if (abstractRequestCallback != null) {
            abstractRequestCallback.setErrorView(errorView);
        }
    }

}
