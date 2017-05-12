#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mLine.h"
#include "mPoint.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MLine> ("Lines", 1, 0, "MeasureLine");
    qmlRegisterType<MPoint> ("Points", 1, 0, "MeasureLinePoint");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
