package com.example.ws;

import android.util.Log;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class JsonStation
{
   static JSONObject[] Stations = new JSONObject[2];

    static JSONParser parser = new JSONParser();

    public static JSONObject[] parseStationData(String line)
    {
        try {
            JSONObject json = (JSONObject) parser.parse(line);
            Stations[0] = (JSONObject) parser.parse(json.get("0").toString());
            Stations[1] = (JSONObject) parser.parse(json.get("1").toString());

        }catch (Exception ex)
        {
            Log.e("JsonStation", "Error in parsing" + ex);
        }

        return Stations;
    }

}
