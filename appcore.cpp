#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{

}

void AppCore::crash()
{
    QObject *p = nullptr;
    p->setParent(this);
}
