#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "hid/hidservice.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QmlApplicationViewer viewer;

    HIDService hidService;
    hidService.registerService();

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/bluetoothtests/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
