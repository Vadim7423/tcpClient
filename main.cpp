#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "app.h"

QObject *app_instance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    static App object;
    engine->rootContext()->setContextProperty("volt_meter_model", &object.voltMeterModel());
    engine->setObjectOwnership(&object, QQmlEngine::CppOwnership);
    return &object;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    qmlRegisterSingletonType<App>("testQtClient", 1, 0, "App",
                                  &app_instance);
    qmlRegisterType<Channel>("testQtClient", 1, 0, "Channel");

    engine.loadFromModule("testQtClient", "Main");

    return app.exec();
}
