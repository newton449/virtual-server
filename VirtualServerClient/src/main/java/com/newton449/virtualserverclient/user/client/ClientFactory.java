package com.newton449.virtualserverclient.user.client;

import com.google.gwt.event.shared.SimpleEventBus;
import com.google.gwt.place.shared.PlaceController;
import com.google.gwt.user.client.ui.HasText;
import com.google.web.bindery.event.shared.EventBus;

/**
 *
 * @author Steven
 */
public class ClientFactory {

    public static ClientFactory getInstance() {
        return clientFactory;
    }
    static ClientFactory clientFactory = new ClientFactory();
    private EventBus eventBus = new SimpleEventBus();
    private PlaceController placeController = new PlaceController(eventBus);
    private LoadingPage loadingPage = new LoadingPage();
    private MainFrame mainFrame = new MainFrame();
    private HasText errorPanel;

    /**
     * It cannot be created by other class. Make it visible for GWT (not
     * private).
     */
    ClientFactory() {
    }

    public EventBus getEventBus() {
        return eventBus;
    }

    public PlaceController getPlaceController() {
        return placeController;
    }

    public LoadingPage getLoadingPage() {
        return loadingPage;
    }

    public MainFrame getMainFrame() {
        return mainFrame;
    }
}
