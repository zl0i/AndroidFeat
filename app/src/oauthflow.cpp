#include "oauthflow.h"

OAuthFlow::OAuthFlow() : QObject(nullptr)
{
    QAndroidJniObject activity = QtAndroid::androidActivity();
    JNINativeMethod methods[] = {
        {"onVkLogin", "(Ljava/lang/String;)V", reinterpret_cast<void*>(OAuthFlow::onVkLogin)},
        {"onYaLogin", "(Ljava/lang/String;)V", reinterpret_cast<void*>(OAuthFlow::onYaLogin)}
    };
    jclass activity_class = env->GetObjectClass(activity.object<jobject>());
    env->RegisterNatives(activity_class, methods, sizeof (methods) / sizeof(methods[0]));
    env->DeleteLocalRef(activity_class);
}

void OAuthFlow::onVkLogin(JNIEnv *env, jobject obj, jstring msg)
{
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject data = msg;
    qDebug() << "vk token:" << data.toString();
}

void OAuthFlow::onYaLogin(JNIEnv *env, jobject obj, jstring msg)
{
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject data = msg;
    qDebug() << "ya token:" << data.toString();
}

void OAuthFlow::oAuthLogin(QString service)
{
#ifdef Q_OS_ANDROID
     QAndroidJniObject activity = QtAndroid::androidActivity();
    if(service == "vk") {
        activity.callMethod<void>("vkLogin", "()V");
    } else if(service == "ya") {
       activity.callMethod<void>("yaLogin", "()V");
    }
#endif
}
