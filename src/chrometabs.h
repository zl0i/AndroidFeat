#ifndef CHROMETABS_H
#define CHROMETABS_H

#include <QObject>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidIntent>
#endif

class ChromeTabs : public QObject
{
    Q_OBJECT
public:
    ChromeTabs();

public slots:
    void openChromeTabs(QString url);
};

#endif // CHROMETABS_H
