package com.zloi.firebase.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.net.Uri;

import com.vk.api.sdk.VK;
import com.vk.api.sdk.auth.*;
import com.vk.api.sdk.utils.VKUtils;

import java.util.Collection;
import java.util.ArrayList;

import org.qtproject.qt5.android.bindings.QtActivity;

import android.util.Log;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {

    final String TAG = "MainActivity";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        String[] fingerprints = VKUtils.getCertificateFingerprint(this, this.getPackageName());
        Log.d(TAG, String.join(",", fingerprints));
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

    public void vkLogin() {
        Collection<VKScope> scopes = new ArrayList<>();
        VK.login(this, scopes);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Log.d(TAG, "requestCode = " + requestCode + ", resultCode = " + resultCode);

        if (!VK.onActivityResult(requestCode, resultCode, data, new VKAuthCallback() {

            @Override
            public void onLogin(VKAccessToken vkAccessToken) {
                onVkLogin(vkAccessToken.getAccessToken());
                Log.d(TAG, vkAccessToken.getAccessToken());
                Log.d(TAG, String.valueOf(VK.getUserId()));
            }

            @Override
            public void onLoginFailed(int i) {

            }

        })) {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    public native void signalIntent(String data);
    public native void onVkLogin(String token);
}
