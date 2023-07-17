package com.example.ws;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.app.Notification;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;


public class MainActivity extends AppCompatActivity {

    private JSONObject[] stations = new JSONObject[2];

    private String line = new String();

    private Boolean wifiConnected;

    private Button headerButton, devSaveButton;
    private TextView devIp, devHeader;
    FetchData fd  = new FetchData();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_main);

        Log.i("net", Boolean.toString(checkNetworkConnection()));



         timer.schedule(doAsynchronousTask, 0, 5000); //execute in every 10 minutes

        devSaveButton = findViewById(R.id.devIpSave);
        devHeader = findViewById(R.id.devIpHeader);
        devIp = findViewById(R.id.devIpTextBox);
        devIp.setText(fd.getIp());
        hideDev();


        headerButton = findViewById(R.id.headerButton);
        headerButton.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                Log.i("header","Pressed Long!");
                if(!isDevVissible())
                    exposeDev();
                else
                    hideDev();

                return false;
            }
        });
        devSaveButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                fd.setIp(devIp.getText().toString());
                Log.i("Dev", "pressed Save");

            }
        });
    }



    final Handler handler = new Handler();
    Timer timer = new Timer();


    TimerTask doAsynchronousTask = new TimerTask() {
        @Override
        public void run() {
            Thread th = new Thread(fd);
            handler.post(new Runnable() {
                public void run() {

                    try {
                        if(checkNetworkConnection()) {
                            Log.i("timer", "run");
                            th.start();
                            th.join();
                            line = fd.getLine();
                            Log.i("timer", line);

                            stations = JsonStation.parseStationData(line);
                            setView(stations);
                        }
                        else {
                            openDialog();
                            final Handler handler = new Handler();
                            handler.postDelayed(new Runnable() {
                                @Override
                                public void run() {
                                    doAsynchronousTask.run();                                }
                            }, 12000);

                        }
                    } catch (Exception e) {
                        Log.i("time", "error in timer " + e );
                    }
                }
            });
        }
    };


    void setView(JSONObject stations[])
    {
        TextView mtemp = (TextView) findViewById(R.id.textView5);
        TextView mhum = (TextView) findViewById(R.id.textView4);
        TextView mpress = (TextView) findViewById(R.id.textView3);
        TextView malt = (TextView) findViewById(R.id.textView6);

        TextView stemp = (TextView) findViewById(R.id.temp2);
        TextView shum = (TextView) findViewById(R.id.hum2);

        mtemp.setText(stations[0].get("temp").toString() + " \u2103");
        mhum.setText(stations[0].get("humidity").toString() + "%");
        mpress.setText(stations[0].get("pressure").toString());
        malt.setText(stations[0].get("alt").toString());

        stemp.setText(stations[1].get("temp").toString() + " \u2103");
        shum.setText(stations[1].get("humidity").toString() + "%");

        Log.i("thread", "ok");



    }

    private boolean checkNetworkConnection()
    {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connectivityManager.getActiveNetworkInfo();

        if(networkInfo != null && networkInfo.isConnected())
        {
            return networkInfo.getType() == ConnectivityManager.TYPE_WIFI;
        }
        return false;
    }

    public void openDialog()
    {
        WifiDialog wd = new WifiDialog();
        wd.show(getSupportFragmentManager(), "Wifi Dialog");
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater =  getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    // Dev
    private boolean isDevVissible()
    {
        if(devSaveButton.getVisibility() == View.VISIBLE &&
                (devIp.getVisibility() == View.VISIBLE) &&
                (devHeader.getVisibility() == View.VISIBLE))
            return true;
        else
            return false;
    }

    private void exposeDev()
    {
        devSaveButton.setVisibility(View.VISIBLE);
        devHeader.setVisibility(View.VISIBLE);
        devIp.setVisibility(View.VISIBLE);
    }
    private void hideDev()
    {
        devSaveButton.setVisibility(View.GONE);
        devHeader.setVisibility(View.GONE);
        devIp.setVisibility(View.GONE);
    }

    public void notification(String title, String text)
    {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(MainActivity.this, "Notification");
        builder.setContentTitle(title);
        builder.setContentText(text);
        builder.setAutoCancel(true);
    }
}



