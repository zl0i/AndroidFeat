#include "notificationworker.h"


NotificationWorker &NotificationWorker::instansce()
{
    static NotificationWorker p_instance;
    return  p_instance;
}

NotificationWorker::NotificationWorker()
{
    m_javaClass = QAndroidJniObject("com/zloi/firebase/test/Notification");
    JNINativeMethod methods[] = {
           {"signalMessage", "(Ljava/lang/String;)V", reinterpret_cast<void*>(NotificationWorker::callbackMessage)},
           {"signalNewToken", "(Ljava/lang/String;)V", reinterpret_cast<void*>(NotificationWorker::newToken)}
    };

    jclass objectClass = env->GetObjectClass(m_javaClass.object<jobject>());
    //https://www.cs.rit.edu/usr/local/jdk/docs/specs/jni/functions.html
    env->RegisterNatives(objectClass, methods, sizeof (methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

QString NotificationWorker::getToken()
{
    QAndroidJniObject token = m_javaClass.callObjectMethod<jstring>("getToken");
    return token.toString();
}

void NotificationWorker::sendNotification(QString, QString)
{
    //char *titleChar = title.toLocal8Bit().data();
    //char *bodyChar = body.toLocal8Bit().data();
    //qDebug() << titleChar << bodyChar;
    m_javaClass.callMethod<jint>("sendNotification", "(Ljava/lang/String;Ljava/lang/String;)V", "test", "test"); //error????
}

QJsonArray NotificationWorker::getEvents()
{
    QAndroidJniObject events = m_javaClass.callObjectMethod<jstring>("getEvents");
    QStringList list = events.toString().split(";", Qt::SkipEmptyParts);
    QJsonArray arr;
    for(int i = 0; i < list.size(); i++) {
       QJsonObject obj = QJsonDocument::fromJson(list.at(i).toLocal8Bit()).object();
       arr.append(obj);
    }
    return  arr;
}

void NotificationWorker::eventsClear()
{
    m_javaClass.callMethod<void>("eventsClear");
}

void NotificationWorker::callbackMessage(JNIEnv  *env, jobject obj, jstring data) {
    Q_UNUSED(env)
    Q_UNUSED(obj)   
    QAndroidJniObject jdata = data;
    QJsonDocument jsonDocument;
    jsonDocument = jsonDocument.fromJson(jdata.toString().toLocal8Bit());
    emit instansce().sendingMessage(jsonDocument.object());
}

void NotificationWorker::newToken(JNIEnv  *env, jobject obj, jstring msg) {
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject jObject = msg;
    emit instansce().updateToken(jObject.toString());
}
