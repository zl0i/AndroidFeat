#include "deeplinkshandler.h"

#include <QAndroidIntent>

DeepLinksHandler::DeepLinksHandler()
{
    QAndroidJniObject classObject = QtAndroid::androidActivity();
    QAndroidJniObject uri = classObject.callObjectMethod<jstring>("getLinkUri");   
    link.setUrl(uri.toString());    
}

QString DeepLinksHandler::getLink()
{
    return link.toString();
}

