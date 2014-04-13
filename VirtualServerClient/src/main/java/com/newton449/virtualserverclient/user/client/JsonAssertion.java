package com.newton449.virtualserverclient.user.client;

/**
 *
 * @author Steven
 */
public class JsonAssertion {

    public static void propertyNotNull(Object obj, String propertyName) {
        if (obj == null) {
            throw new IllegalArgumentException("Failed to find property \"" + propertyName + "\" in the JSON string.");
        }
    }
}
