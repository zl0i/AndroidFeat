package com.zloi.firebase.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.net.Uri;

import org.qtproject.qt5.android.bindings.QtActivity;

import android.util.Log;

public class CustomActivity extends org.qtproject.qt5.android.bindings.QtActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        signalIntent(intent.getData().toString());
    }

    public String getLinkUri() {
        Intent intent = getIntent();
        Uri appLinkData = intent.getData();
        if (appLinkData != null) {
            return appLinkData.toString();
        }
        return "";
    }

    public native void signalIntent(String data);
}
