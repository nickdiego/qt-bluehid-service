#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeContext>

#include "qmlapplicationviewer.h"

#include "hidserver.h"
#include "hidstringsender.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qmlRegisterUncreatableType<HIDServer>("bluetests", 1, 0, "HIDServer",
                                          "Only used for reading HIDServer properties");

    // FIXME: If server is declared as a object,
    //        app crashes at several points!
    QScopedPointer<HIDServer> server(new HIDServer());
    QScopedPointer<HIDStringSender> stringSender(new HIDStringSender(server.data()));
    server->start();

    viewer->rootContext()->setContextProperty(QLatin1String("hidServer"), server.data());
    viewer->rootContext()->setContextProperty(QLatin1String("hidStringSender"), stringSender.data());

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/simplestringsender/main.qml"));
    viewer->showExpanded();

    app->exec();

    qDebug() << "Mainloop finished";
    // FIXME: App is aborting when destructing hidServer.
    //server->stop();

    return 0;
}
