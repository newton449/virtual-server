package com.newton449.virtualserverclient.user.client;

import com.google.gwt.place.shared.Place;
import com.google.gwt.place.shared.PlaceHistoryMapper;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Steven
 */
public class SimplePlaceHistoryMapper implements PlaceHistoryMapper {

    Map<String, Place> placeMap = new HashMap<>();
    Map<Place, String> tokenMap = new HashMap<>();

    public void put(String token, Place place) {
        placeMap.put(token, place);
        tokenMap.put(place, token);
    }

    @Override
    public Place getPlace(String token) {
        return placeMap.get(token);
    }

    @Override
    public String getToken(Place place) {
        return tokenMap.get(place);
    }

}
