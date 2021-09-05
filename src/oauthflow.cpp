#include "oauthflow.h"

OAuthFlow::OAuthFlow() : QObject(nullptr)
{
    QAndroidJniObject activity = QtAndroid::androidActivity();
    JNINativeMethod methods[] = {
        {"onVkLogin", "(Ljava/lang/String;)V", reinterpret_cast<void*>(OAuthFlow::onVkLogin)},
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
    qDebug() << "token:" << data.toString();
}

void OAuthFlow::vkLogin()
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("vkLogin", "()V");
#endif
}
