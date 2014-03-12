package com.newton449.virtualserverclient.home.client;

import com.google.gwt.core.client.EntryPoint;
import com.newton449.virtualserverclient.user.client.Initializer;
import com.newton449.virtualserverclient.user.client.SimplePlaceHistoryMapper;

/**
 * The EntryPoint for "Home" module.
 *
 * @author Steven
 */
public class HomeEntry implements EntryPoint {

    @Override
    public void onModuleLoad() {
        Initializer initializer = new Initializer();
        SimplePlaceHistoryMapper mapper = new SimplePlaceHistoryMapper();
        HomePlace defaultPlace = new HomePlace();
        mapper.put("", defaultPlace);
        mapper.put("about", new AboutPlace());
        initializer.initiate(new HomeActivityMapper(), mapper, defaultPlace);
    }

}
