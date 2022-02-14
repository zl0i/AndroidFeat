#ifndef SMSRECEIVER_H
#define SMSRECEIVER_H

#include <QObject>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroidExtras>
#include <QAndroidJniEnvironment>
#endif


class SMSReceiver : public QObject
{
    Q_OBJECT
public:    
    SMSReceiver(SMSReceiver&) = delete;
    SMSReceiver operator=(const SMSReceiver&) = delete;

    static SMSReceiver *instance();

private:
    SMSReceiver();
    static SMSReceiver *_instance;

#ifdef Q_OS_ANDROID
    static void newCode(JNIEnv  *env, jobject obj, jstring data);


    QAndroidJniObject receiver;
    QAndroidJniEnvironment env;
#endif

signals:
    void receivedCode(QString code);

};

#endif // SMSRECEIVER_H
