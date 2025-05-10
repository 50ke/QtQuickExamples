#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "PointCloudGeometry.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PointCloudGeometry>("PointCloud", 1, 0, "PointCloudGeometry");


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PointCloudVisualizationQuick3D", "Main");

    return app.exec();
}
