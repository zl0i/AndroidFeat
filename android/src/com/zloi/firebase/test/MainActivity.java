package com.zloi.firebase.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.net.Uri;

import com.vk.api.sdk.VK;
import com.vk.api.sdk.auth.*;
import com.yandex.authsdk.*;

import java.util.Collection;
import java.util.ArrayList;

import org.qtproject.qt5.android.bindings.QtActivity;

import android.util.Log;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {

    final String TAG = "MainActivity";
    private YandexAuthSdk sdk;
    final int REQUEST_CODE_YANDEX = 285;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sdk = new YandexAuthSdk(getApplicationContext(), new YandexAuthOptions.Builder(getApplicationContext())
                        .build());
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

    public void yaLogin() {
        final YandexAuthLoginOptions.Builder loginOptionsBuilder =  new YandexAuthLoginOptions.Builder();
        final Intent intent = sdk.createLoginIntent(loginOptionsBuilder.build());
        startActivityForResult(intent, REQUEST_CODE_YANDEX);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "requestCode = " + requestCode + ", resultCode = " + resultCode);

        if (requestCode == REQUEST_CODE_YANDEX) {
            try {
                final YandexAuthToken yandexAuthToken = sdk.extractToken(resultCode, data);
                if (yandexAuthToken != null) {
                    onYaLogin( yandexAuthToken.getValue());
                } else {
                    Log.d(TAG, "deny");
                }
            } catch (YandexAuthException e) {
                Log.d(TAG, "error");
            }
        } else if(requestCode == 282) {
            VK.onActivityResult(requestCode, resultCode, data, new VKAuthCallback() {

                @Override
                public void onLogin(VKAccessToken vkAccessToken) {
                    onVkLogin(vkAccessToken.getAccessToken());
                }

                @Override
                public void onLoginFailed(int i) {

                }
            });
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    public native void signalIntent(String data);
    public native void onVkLogin(String token);
    public native void onYaLogin(String token);
}
