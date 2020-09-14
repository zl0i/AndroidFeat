package com.zloi.firebase.test;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.app.ActivityManager.RunningAppProcessInfo;

import androidx.core.app.NotificationCompat;
import android.os.Build;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.media.RingtoneManager;
import android.net.Uri;

import android.util.Log;

import java.util.Map;
import org.json.*;
import java.util.List;
import java.util.ArrayList;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.iid.FirebaseInstanceId;
import com.google.firebase.messaging.RemoteMessage;

import com.zloi.firebase.test.R;

import org.qtproject.qt5.android.bindings.QtActivity;

public class Notification  extends FirebaseMessagingService {

    private static final String TAG = "FirebaseMsgService";

    private static ArrayList<JSONObject> events = new ArrayList<>();

    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
         final Map<String, String> data = remoteMessage.getData();

         if(isAppRunning("com.zloi.firebase.test")) {
             if(isAppRunningForeground("com.zloi.firebase.test")) {
                 final JSONObject json = new JSONObject(data);
                 signalMessage(json.toString());
             } else {
                 final JSONObject json = new JSONObject(data);
                 signalMessage(json.toString());
                 final String title = data.get("title");
                 final String body = data.get("body");
                 if(!title.isEmpty() || !body.isEmpty()) {
                     sendNotification(title, body);
                 }
             }
         } else {
            pushEvent(new JSONObject(data));
            final String title = data.get("title");
            final String body = data.get("body");
            if(!title.isEmpty() || !body.isEmpty()) {
                sendNotification(title, body);
            }
         }        
    }

    @Override
    public void onNewToken(String mToken) {
        super.onNewToken(mToken);
        signalNewToken(mToken);
        Log.e(TAG + " TOKEN", mToken);
    }

    public String getToken() {
        return FirebaseInstanceId.getInstance().getToken();
    }

    private void sendNotification(String title, String body) {
        Intent intent = new Intent(this, QtActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent,
                       PendingIntent.FLAG_ONE_SHOT);

        final String channelId = getString(R.string.default_notification_channel_id);
        Uri defaultSoundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        final int colorAccent = getColor(R.color.colorAccent);

        NotificationCompat.Builder notificationBuilder =
                new NotificationCompat.Builder(this, channelId)
                        .setSmallIcon(R.drawable.notificationicon)
                        .setContentTitle(title)
                        .setContentText(body)
                        .setAutoCancel(true)
                        .setSound(defaultSoundUri)
                        .setColor(colorAccent)
                        .setContentIntent(pendingIntent);

        NotificationManager notificationManager =
                            (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(channelId,
                    "Channel human readable title",
                    NotificationManager.IMPORTANCE_DEFAULT);
            notificationManager.createNotificationChannel(channel);
        }
        notificationManager.notify(0,  notificationBuilder.build());
   }

    private void pushEvent(JSONObject event) {
         events.add(event);
    }

    public String getEvents() {
        String listString = "";
        for (JSONObject data : events)  {
            listString += data.toString() + ";";
        }
        return listString;
    }

    public void eventsClear() {
        events.clear();
    }

    private Boolean isAppRunningForeground(final String packageName) {
        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        final List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
        if (appProcesses == null) {
            return false;
        }
        for (RunningAppProcessInfo appProcess : appProcesses) {
            if (appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND && appProcess.processName.equals(packageName)) {
                return true;
            }
        }
        return false;
    }

    private Boolean isAppRunning(final String packageName) {
           final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
           final List<RunningTaskInfo> activitys = activityManager.getRunningTasks(Integer.MAX_VALUE);
           for (int i = 0; i < activitys.size(); i++) {
               if (activitys.get(i).topActivity.toString().equalsIgnoreCase("ComponentInfo{" + packageName + "/org.qtproject.qt5.android.bindings.QtActivity}")) {
                   return true;
               }
           }
           return false;
    }

    public native void signalMessage(String data);
    public native void signalNewToken(String token);

}
