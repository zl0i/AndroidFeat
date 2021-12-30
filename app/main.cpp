#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/appcore.h"
#include "src/notificationworker.h"
#include "src/oauthflow.h"
#include "src/deeplinkshandler.h"
#include "src/chrometabs.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    NotificationWorker *worker = NotificationWorker::instance();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    AppCore core;
    DeepLinksHandler dlHandler;
    qDebug() << "push token:" << worker->getToken();
    engine.rootContext()->setContextProperty("_notify", worker);
    engine.rootContext()->setContextProperty("_oauth", new OAuthFlow());
    engine.rootContext()->setContextProperty("_appCore", &core);
    engine.rootContext()->setContextProperty("_deepLinks", &dlHandler);
    engine.rootContext()->setContextProperty("_tabs", new ChromeTabs());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
