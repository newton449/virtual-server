package com.newton449.virtualserverclient.user.client;

import com.google.gwt.activity.shared.ActivityManager;
import com.google.gwt.activity.shared.ActivityMapper;
import com.google.gwt.core.client.JsArray;
import com.google.gwt.core.client.JsonUtils;
import com.google.gwt.http.client.Request;
import com.google.gwt.http.client.RequestBuilder;
import com.google.gwt.http.client.Response;
import com.google.gwt.place.shared.Place;
import com.google.gwt.place.shared.PlaceController;
import com.google.gwt.place.shared.PlaceHistoryHandler;
import com.google.gwt.place.shared.PlaceHistoryMapper;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.web.bindery.event.shared.EventBus;
import com.newton449.virtualserverclient.user.client.model.InitializationModel;
import com.newton449.virtualserverclient.user.client.model.MenuItemModel;

/**
 *
 * @author Steven
 */
public class Initializer {

    public void initiate(ActivityMapper activityMapper, PlaceHistoryMapper placeHistoryMapper, Place defaultPlace) {
        // Creates ClientFactory
        ClientFactory clientFactory = ClientFactory.getInstance();
        EventBus eventBus = clientFactory.getEventBus();
        PlaceController placeController = clientFactory.getPlaceController();

        // Starts ActivityManager for the main widget with our ActivityMapper
        ActivityManager activityManager = new ActivityManager(activityMapper, eventBus);
        MainFrame mainFrame = clientFactory.getMainFrame();
        mainFrame.setWidget(clientFactory.getLoadingPage());
        activityManager.setDisplay(mainFrame);

        // Starts PlaceHistoryHandler with our PlaceHistoryMapper
        PlaceHistoryHandler historyHandler = new PlaceHistoryHandler(placeHistoryMapper);
        historyHandler.register(placeController, eventBus, defaultPlace);

        RootPanel.get().add(mainFrame);

        // Loads data for MainFrame
        prepare(mainFrame);

        // Goes to the place represented on URL else default place
        historyHandler.handleCurrentHistory();
    }

    private void prepare(final MainFrame mainFrame) {
        RequestSender sender = new RequestSender(RequestBuilder.GET, "/home/menu_list");
        sender.setErrorHandler(new GlobalMessagePanel());
        sender.setCallback(new AbstractRequestCallback() {

            @Override
            public void onSuccess(Request request, Response response) {
                InitializationModel im = JsonUtils.safeEval(response.getText());
                JsArray<MenuItemModel> items = im.getMenu();
                for (int i = 0; i < items.length(); i++) {
                    mainFrame.addMenuItem(items.get(i).getName(), items.get(i).getUrl(), items.get(i).getTitle());
                }
            }
        });
        sender.send();
    }
}
