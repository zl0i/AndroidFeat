#include "notificationworker.h"


NotificationWorker* NotificationWorker::_instance = nullptr;

NotificationWorker *NotificationWorker::instance()
{
    if(_instance == nullptr) {
        _instance = new NotificationWorker();
    }
    return _instance;
}


QString NotificationWorker::getToken()
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject token = notification.callObjectMethod<jstring>("getToken");
    return token.toString();
#elif Q_OS_IOS
    return devicePushToken;
#else
    return "";
#endif
}

//https://www.cs.rit.edu/usr/local/jdk/docs/specs/jni/functions.html
NotificationWorker::NotificationWorker()
{
#ifdef Q_OS_ANDROID
    notification = QAndroidJniObject("com/zloi/firebase/test/Notification");
    JNINativeMethod notification_methods[] = {
        {"signalMessage", "(Ljava/lang/String;)V", reinterpret_cast<void*>(NotificationWorker::callbackMessage)},
        {"signalNewToken", "(Ljava/lang/String;)V", reinterpret_cast<void*>(NotificationWorker::newToken)}
    };
    jclass notification_class = env->GetObjectClass(notification.object<jobject>());
    env->RegisterNatives(notification_class, notification_methods, sizeof (notification_methods) / sizeof(notification_methods[0]));
    env->DeleteLocalRef(notification_class);

    QAndroidJniObject activity = QtAndroid::androidActivity();
    JNINativeMethod activity_methods[] = {
        {"signalIntent", "(Ljava/lang/String;)V", reinterpret_cast<void*>(NotificationWorker::newDataPush)},
    };
    jclass activity_Class = env->GetObjectClass(activity.object<jobject>());
    env->RegisterNatives(activity_Class, activity_methods, sizeof (activity_methods) / sizeof(activity_methods[0]));
    env->DeleteLocalRef(activity_Class);
#endif
}


QJsonObject NotificationWorker::getDataPush()
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject intent = activity.callObjectMethod("getIntent", "()Landroid/content/Intent;");
    QAndroidJniObject data = intent.callObjectMethod("getData", "()Landroid/net/Uri;");

    QUrl uri(data.toString());
    QUrlQuery query(uri.query());
    QList<QPair<QString, QString>> list = query.queryItems();
    QJsonObject obj {
        {"host", uri.host() },
        {"path", uri.path() },
    };
    QJsonObject params;
    for(int i = 0; i < list.length(); i++) {
        params.insert(list.at(i).first, list.at(i).second);
    }
    obj.insert("params", params);
    return obj;
#else
    return QJsonObject();
#endif
}

void NotificationWorker::sendNotification(QString title, QString body, QString data)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject titleJni = QAndroidJniObject::fromString(title);
    QAndroidJniObject messageJni = QAndroidJniObject::fromString(body);
    QAndroidJniObject dataJni = QAndroidJniObject::fromString(data);
    QAndroidJniObject uriJni = QAndroidJniObject::callStaticObjectMethod(
                "com/zloi/firebase/test/Notification",
                "parseUri",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                dataJni.object<jstring>());

    QAndroidJniObject::callStaticMethod<void>(
                "com/zloi/firebase/test/Notification",
                "sendNotification",
                "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Landroid/net/Uri;)V",
                QtAndroid::androidContext().object(),
                titleJni.object<jstring>(), messageJni.object<jstring>(), uriJni.object<jobject>());
#else
    Q_UNUSED(title)
    Q_UNUSED(body)
    Q_UNUSED(data)
#endif
}

#ifdef Q_OS_ANDROID
void NotificationWorker::callbackMessage(JNIEnv  *env, jobject obj, jstring msg) {
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject data = msg;
    QJsonDocument doc = QJsonDocument::fromJson(data.toString().toLocal8Bit());
    emit instance()->sendingMessage(doc.object());
}

void NotificationWorker::newToken(JNIEnv *env, jobject obj, jstring msg) {
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject jObject = msg;
    emit instance()->updateToken(jObject.toString());
}

void NotificationWorker::newDataPush(JNIEnv *env, jobject obj, jstring msg) {
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject data = msg;
    QUrl uri(data.toString());
    QUrlQuery query(uri.query());
    QList<QPair<QString, QString>> list = query.queryItems();
    QJsonObject json {
        {"host", uri.host() },
        {"path", uri.path() },
    };
    QJsonObject params;
    for(int i = 0; i < list.length(); i++) {
        params.insert(list.at(i).first, list.at(i).second);
    }
    json.insert("params", params);
    emit instance()->updateDataPush(json);
}

#endif
