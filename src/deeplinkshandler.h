#ifndef DEEPLINKSHANDLER_H
#define DEEPLINKSHANDLER_H

#include <QObject>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QUrl>
#include <QDebug>

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
