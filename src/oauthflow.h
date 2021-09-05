#ifndef OAUTHFLOW_H
#define OAUTHFLOW_H

#include <QObject>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroidExtras>
#include <QAndroidJniEnvironment>
#endif

class OAuthFlow: public QObject
{
    Q_OBJECT
public:
    OAuthFlow();

private:
    QAndroidJniEnvironment env;
    static void onVkLogin(JNIEnv  *env, jobject obj, jstring msg);

public slots:
    void vkLogin();

};

#endif // OAUTHFLOW_H
