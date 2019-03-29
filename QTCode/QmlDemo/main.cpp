#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include<QDateTime>
#include<QDebug>
#include"applicationdata.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QDateTime time;
    ApplicationData data;
    engine.rootContext()->setContextProperty("currentDateTime",&data);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
