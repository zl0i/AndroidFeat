#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "appcore.h"
#include "notificationworker.h"
#include "deeplinkshandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    NotificationWorker &worker = NotificationWorker::instansce();


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AppCore core;
    DeepLinksHandler dlHandler;
    qDebug() << "push token:" << worker.getToken();
    engine.rootContext()->setContextProperty("notify", &worker);
    engine.rootContext()->setContextProperty("appCore", &core);
    engine.rootContext()->setContextProperty("_deepLinks", &dlHandler);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
