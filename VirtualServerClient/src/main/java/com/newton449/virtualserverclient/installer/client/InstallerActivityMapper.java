package com.newton449.virtualserverclient.installer.client;

import com.google.gwt.activity.shared.Activity;
import com.google.gwt.activity.shared.ActivityMapper;
import com.google.gwt.place.shared.Place;
import com.newton449.virtualserverclient.user.client.NotFoundActivity;

/**
 *
 * @author Steven
 */
public class InstallerActivityMapper implements ActivityMapper {

    @Override
    public Activity getActivity(Place place) {
        if (place instanceof CloneServerPlace) {
            return new CloneServerActivity();
        }
        return new NotFoundActivity();
    }

}
