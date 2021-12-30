#include "deeplinkshandler.h"



DeepLinksHandler::DeepLinksHandler()
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject intent = activity.callObjectMethod("getIntent", "()Landroid/content/Intent;");
    QAndroidJniObject data = intent.callObjectMethod("getData", "()Landroid/net/Uri;");

    link.setUrl(data.toString());
#endif
}

QString DeepLinksHandler::getLink()
{
    return link.toString();
}

