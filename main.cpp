#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mLine.h"
#include "mAngle.h"
#include "bcurve.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MLine> ("Lines", 1, 0, "MeasureLine");
    qmlRegisterType<MPoint> ("Points", 1, 0, "MeasureLinePoint");
    qmlRegisterType<BCurve> ("CurveM", 1, 0, "BCurve");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
