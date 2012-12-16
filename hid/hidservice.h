#ifndef HIDSERVICE_H
#define HIDSERVICE_H

#include <QObject>
#include <QBluetoothServiceInfo>

QTM_BEGIN_NAMESPACE
class QBluetoothServiceInfo;
QTM_END_NAMESPACE
QTM_USE_NAMESPACE

class HIDService : public QObject
{
    Q_OBJECT
public:
    explicit HIDService(QObject *parent = 0);
    void registerService();

    static const int HIDDescSize;
    static const quint8 HIDDesc[];

private:
    void addHIDSpecificInfo();

    QBluetoothServiceInfo serviceInfo;
};

#endif // HIDSERVICE_H
