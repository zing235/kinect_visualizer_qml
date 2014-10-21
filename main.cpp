#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQml>
#include "kinectcamera.h"
#include "ImageValue.h"
#include <QtQuick/QQuickView>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<KinectCamera>("KinectCamera",1,0,"KinectCamera");
    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("imagevalue",new ImageValue);
    viewer.setMainQmlFile(QStringLiteral("qml/kinecttest/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
