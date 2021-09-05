package com.zloi.firebase.test;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;

import androidx.core.app.NotificationCompat;
import android.os.Build;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;

import org.json.JSONObject;
import java.util.Map;
import android.util.Log;
import java.util.List;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.iid.FirebaseInstanceId;
import com.google.firebase.messaging.RemoteMessage;

import com.zloi.firebase.test.MainActivity;

public class Notification extends FirebaseMessagingService {

    private static final String TAG = "FirebaseMsgService";

    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
        final Map<String, String> data = remoteMessage.getData();        

        try {
            if(isAppRunningForeground("org.fusion.board")) {
                JSONObject json = new JSONObject(data);
                signalMessage(json.toString());
            } else {
                Uri uri = Uri.parse(joinData(data));
                final String title = data.get("title");
                final String body = data.get("body");                

                sendNotification(getApplicationContext(), title, body, uri);
            }
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG + " onMessageReceived: [ERROR]", e.getMessage());
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

    private String joinData(Map<String, String> map) {
        String uri = "fusion://fboard.app/" + map.get("type") + "?";
        for (Map.Entry<String, String> entry : map.entrySet()) {
            uri += "&" + entry.getKey() + "=" + entry.getValue();
        }
        return uri;
    }

    public static void sendNotification(Context context, String title, String body, Uri data) {
        try {
            Intent intent = new Intent(context, MainActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
            intent.setData(data);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, intent,
                    PendingIntent.FLAG_UPDATE_CURRENT);

            NotificationManager manager = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);

            NotificationCompat.Builder notificationBuilder;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_DEFAULT;
                NotificationChannel notificationChannel = new NotificationChannel("fcm_default_channel", "Channel human readable title",
                NotificationManager.IMPORTANCE_DEFAULT);
                manager.createNotificationChannel(notificationChannel);
                notificationBuilder = new NotificationCompat.Builder(context, notificationChannel.getId());
            } else {
                notificationBuilder = new NotificationCompat.Builder(context);
            }

            notificationBuilder
                    .setSmallIcon(R.drawable.notificationicon)
                    .setContentTitle(title)
                    .setContentText(body)
                    .setDefaults(NotificationCompat.DEFAULT_SOUND)
                    .setColor(context.getColor(R.color.colorAccent))
                    .setAutoCancel(true)
                    .setContentIntent(pendingIntent);

            manager.notify((int) System.currentTimeMillis(), notificationBuilder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Uri parseUri(String data) {
        return Uri.parse(data);
    }

    private Boolean isAppRunningForeground(final String packageName) {
        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        final List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
        if (appProcesses == null) {
            return false;
        }
        for (RunningAppProcessInfo appProcess : appProcesses) {
            if (appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND
                    && appProcess.processName.equals(packageName)) {
                return true;
            }
        }
        return false;
    }

    public native void signalMessage(String data);
    public native void signalNewToken(String token);
}
