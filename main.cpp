#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeContext>

#include "qmlapplicationviewer.h"

#include "hid/hidserver.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QmlApplicationViewer viewer;

    HIDServer server;

    viewer.rootContext()->setContextProperty("hidServer", &server);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/bluetoothtests/main.qml"));
    viewer.showExpanded();

    app->exec();
    server.stop();
    return 0;
}
