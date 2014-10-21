#ifndef KINECTCAMERA_H
#define KINECTCAMERA_H
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>
#include "OpenNI.h"
class KinectCamera : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString streamsource READ getstreamsource WRITE setstreamsource NOTIFY streamsourceChanged)
public:
    KinectCamera(QQuickItem *parent = 0);

    QString getstreamsource(void) const;
    void setstreamsource(const QString streamsource);
//    void depthprocess(void);
    Q_INVOKABLE void startcamera();
    Q_INVOKABLE void updatecamera();
    Q_INVOKABLE void closecamera();

    void paint(QPainter *painter);

signals:
    void streamsourceChanged();

private:
    QString m_streamsource;

};
#endif // KINECTCAMERA_H
