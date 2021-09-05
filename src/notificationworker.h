#ifndef NOTIFICATIONWORKER_H
#define NOTIFICATIONWORKER_H

#include <QObject>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroidExtras>
#include <QAndroidJniEnvironment>
#endif

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class NotificationWorker : public QObject
{
    Q_OBJECT
public:

    NotificationWorker(NotificationWorker&) = delete;
    NotificationWorker operator=(const NotificationWorker&) = delete;

    static NotificationWorker *instance();



#ifdef Q_OS_IOS
    void registerToken(const void *bytes, size_t length)
    {
        QByteArray ba = QByteArray::fromRawData(static_cast<const char*>(bytes), length);
        devicePushToken = ba.toHex();
        qDebug() << "Register IOS Push Token: " << devicePushToken;
        emit pushTokenRegistered(devicePushToken);
    }

    QJsonObject buildIOSUrl(QJsonObject payload) {
        QJsonObject obj;
        obj.insert("host", "fboard.app");
        obj.insert("path", "/" + payload.value("type").toString());
        QJsonObject params;
        params.insert("id_network", payload.value("id_network").toInt());
        params.insert("id_point", payload.value("id_point").toInt());
        obj.insert("params", params);
        return obj;
    }

    void handleIOSPushMessage(NSString *json)
    {
        QString qjson = QString::fromNSString(json);
        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonObject aps, payload;
        jsonDocument = jsonDocument.fromJson(qjson.toLocal8Bit());
        jsonObject = jsonDocument.object();
        aps = jsonObject["aps"].toObject();
        payload = aps["payload"].toObject();
        emit updateDataPush(buildIOSUrl(payload)); // обработка нового пуша в qml
    }
#endif

private:
    NotificationWorker();
    static NotificationWorker *_instance;
    QString devicePushToken = "";
	
#ifdef Q_OS_ANDROID
    static void callbackMessage(JNIEnv  *env, jobject obj, jstring data);
    static void newDataPush(JNIEnv  *env, jobject obj, jstring data);
    static void newToken(JNIEnv  *env, jobject obj, jstring msg);

    QAndroidJniObject notification;
    QAndroidJniEnvironment env;
#endif
signals:
    void sendingMessage(QJsonObject obj);
    void updateToken(QString token);
    void pushTokenRegistered(QString token);
    void updateDataPush(QJsonObject obj);

public slots:
    QString getToken();
    QJsonObject getDataPush();
    void sendNotification(QString title, QString body, QString icon, QString data);
};



#endif // NOTIFICATIONWORKER_H
