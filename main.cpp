#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeContext>

#include "qmlapplicationviewer.h"

#include "hid/hidserver.h"
#include "hid/hidstringsender.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QmlApplicationViewer viewer;

    qmlRegisterUncreatableType<HIDServer>("bluetests", 1, 0, "HIDServer",
                                          "Only used for reading HIDServer properties");

    HIDServer server;
    HIDStringSender stringSender(server);
    server.start();

    viewer.rootContext()->setContextProperty("hidServer", &server);
    viewer.rootContext()->setContextProperty("hidStringSender", &stringSender);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/bluetoothtests/main.qml"));
    viewer.showExpanded();

    app->exec();
    server.stop();
    return 0;
}
