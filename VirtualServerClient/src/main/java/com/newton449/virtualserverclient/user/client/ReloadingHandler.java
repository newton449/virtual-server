package com.newton449.virtualserverclient.user.client;

/**
 *
 * @author Steven
 */
public interface ReloadingHandler {

    void onReload();

    public static class Utils {

        public ReloadingHandler create(final RequestSender sender) {
            return new ReloadingHandler() {

                @Override
                public void onReload() {
                    sender.send();
                }
            };
        }
    }
}
