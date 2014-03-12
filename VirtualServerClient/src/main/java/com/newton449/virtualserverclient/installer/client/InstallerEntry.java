package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.core.client.EntryPoint;
import com.newton449.virtualserverclient.user.client.Initializer;
import com.newton449.virtualserverclient.user.client.SimplePlaceHistoryMapper;

/**
 *
 * @author Steven
 */
public class InstallerEntry implements EntryPoint {

    @Override
    public void onModuleLoad() {
        Initializer initializer = new Initializer();
        SimplePlaceHistoryMapper mapper = new SimplePlaceHistoryMapper();
        CloneServerPlace defaultPlace = new CloneServerPlace();
        mapper.put("", defaultPlace);
        initializer.initiate(new InstallerActivityMapper(), mapper, defaultPlace);
    }

}
