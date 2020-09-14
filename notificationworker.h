#ifndef NOTIFICATIONWORKER_H
#define NOTIFICATIONWORKER_H

#include <QObject>
#include <QAndroidJniObject>
#include <QtAndroidExtras>
#include <QAndroidJniEnvironment>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>


class NotificationWorker : public QObject
{
    Q_OBJECT
public:

    NotificationWorker(NotificationWorker&) = delete;
    NotificationWorker operator=(const NotificationWorker&) = delete;

    static NotificationWorker &instansce();

    Q_INVOKABLE QString getToken();
    Q_INVOKABLE void sendNotification(QString, QString);

    Q_INVOKABLE QJsonArray getEvents();
    Q_INVOKABLE void eventsClear();

private:
    NotificationWorker();

    static void callbackMessage(JNIEnv  *env, jobject obj, jstring data);
    static void newToken(JNIEnv  *env, jobject obj, jstring msg);

    QAndroidJniObject m_javaClass;
    QAndroidJniEnvironment env;

signals:
     void sendingMessage(QJsonObject data);
     void updateToken(QString token);

public slots:

};

#endif // NOTIFICATIONWORKER_H
