#ifndef DEEPLINKSHANDLER_H
#define DEEPLINKSHANDLER_H

#include <QObject>
#include <QUrl>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidIntent>
#endif

class DeepLinksHandler : public QObject
{
    Q_OBJECT
public:
    DeepLinksHandler();

private:
    QUrl link;

public slots:
    QString getLink();

signals:
    void linkNotEmty(QString link);

};

#endif // DEEPLINKSHANDLER_H
