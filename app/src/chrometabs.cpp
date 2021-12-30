#include "chrometabs.h"

ChromeTabs::ChromeTabs()
{

}

void ChromeTabs::openChromeTabs(QString url)
{
    QAndroidJniObject arg = QAndroidJniObject::fromString(url);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("openChromeTabs", "(Ljava/lang/String;)V", arg.object<jstring>());
}
