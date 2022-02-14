#include "smsreceiver.h"

SMSReceiver* SMSReceiver::_instance = nullptr;

SMSReceiver *SMSReceiver::instance()
{
    if(_instance == nullptr) {
        _instance = new SMSReceiver();
    }
    return _instance;
}

SMSReceiver::SMSReceiver()
{
#ifdef Q_OS_ANDROID
    receiver = QAndroidJniObject("com/zloi/firebase/test/SMSReceiver");
    JNINativeMethod receiver_methods[] = {
        {"signalSMSCode", "(Ljava/lang/String;)V", reinterpret_cast<void*>(SMSReceiver::newCode)},
    };
    jclass receiver_class = env->GetObjectClass(receiver.object<jobject>());
    env->RegisterNatives(receiver_class, receiver_methods, sizeof (receiver_methods) / sizeof(receiver_methods[0]));
    env->DeleteLocalRef(receiver_class);
#endif
}

#ifdef Q_OS_ANDROID
void SMSReceiver::newCode(JNIEnv *env, jobject obj, jstring code)
{
    Q_UNUSED(env)
    Q_UNUSED(obj)
    QAndroidJniObject data = code;
    emit instance()->receivedCode(data.toString());
}
#endif
