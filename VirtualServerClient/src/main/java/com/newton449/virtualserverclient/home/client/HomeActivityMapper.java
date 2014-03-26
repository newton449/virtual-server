package com.newton449.virtualserverclient.home.client;

import com.google.gwt.activity.shared.Activity;
import com.google.gwt.activity.shared.ActivityMapper;
import com.google.gwt.place.shared.Place;
import com.newton449.virtualserverclient.user.client.NotFoundActivity;

/**
 * The ActivityMapper for "Home" module.
 *
 * @author Steven
 */
public class HomeActivityMapper implements ActivityMapper {

    @Override
    public Activity getActivity(Place place) {
        if (place instanceof HomePlace) {
            return new HomeActivity();
        } else if (place instanceof AboutPlace) {
            return new AboutActivity();
        }
        return new NotFoundActivity();
    }

}
