package com.zloi.firebase.test;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.telephony.SmsMessage;
import android.util.Log;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SMSReceiver extends BroadcastReceiver {
    private static final String ACTION = "android.provider.Telephony.SMS_RECEIVED";
    private static final String TAG = "SMSReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent != null && intent.getAction() != null && ACTION.compareToIgnoreCase(intent.getAction()) == 0) {
            Object[] pduArray = (Object[]) intent.getExtras().get("pdus");
            SmsMessage[] messages = new SmsMessage[pduArray.length];
            for (int i = 0; i < pduArray.length; i++) {
                messages[i] = SmsMessage.createFromPdu((byte[]) pduArray[i]);
                if(messages[i].getDisplayOriginatingAddress().equals("TeaSmoke")) {
                    Pattern pattern = Pattern.compile("\\d{5}");
                    Matcher matcher = pattern.matcher(messages[i].getMessageBody());
                    if(matcher.find()) {
                        String code = messages[i].getMessageBody().substring(matcher.start(), matcher.end());
                        Log.d(TAG, "Code:" + code);
                        signalSMSCode(code);
                    }
                }
            }
        }
    }

    public native void signalSMSCode(String code);
}
