package com.example.rooshan.gcmimplementation;

import android.os.Bundle;
import android.util.Log;

import com.google.android.gms.gcm.GcmListenerService;

/**
 * Created by Rooshan on 1/30/2016.
 */
public class MyGcmListenerService extends GcmListenerService {

    //Used to differentiate this class tag in log console
    private static final String CLASSTAG = "MyGcmListenerService";

    //Called when message is received
    @Override
    public void onMessageReceived(String from, Bundle data){

        //log message to console
        String messageFromGCMSever = data.getString("message");
        Log.d(CLASSTAG, "From: " + from);
        Log.d(CLASSTAG,"Message: " + messageFromGCMSever);

        //send a proper notification to device
        sendNoftifcation();
    }

    void sendNoftifcation (){

    }
}
