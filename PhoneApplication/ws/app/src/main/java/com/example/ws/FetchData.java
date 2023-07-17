package com.example.ws;

import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class FetchData implements Runnable
{
    String line = new String();
    String ip = "192.168.1.110";
    @Override
    public void run()
    {

        try {
            URL url = new URL("http://"+ip+"/api?query=all");
            HttpURLConnection hr = (HttpURLConnection) url.openConnection();
            int k = hr.getResponseCode();
            Log.i("data", Integer.toString(k));
            Log.i("data", "In try");

            if (hr.getResponseCode() == 200)
            {
                InputStream im = hr.getInputStream();
                StringBuffer sb = new StringBuffer();
                BufferedReader br = new BufferedReader(new InputStreamReader(im));
                line = br.readLine();
                Log.i("data", line);

            }

        } catch (Exception ex) {
            Log.i("FetchData", "Thread  exception " + ex);
        }

    }
    public String getLine()
    {
        return line;
    }

    public void setIp(String ip)
    {
        this.ip = ip;
    }

    public String getIp() {
        return ip;
    }
}
