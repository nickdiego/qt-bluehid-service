#if defined(MEEGO_HARMATTAN)
#include "hidservicedescriptor_bluez.h"
#else

#ifndef HIDSERVICE_DESCRIPTOR_H
#define HIDSERVICE_DESCRIPTOR_H

#include <QObject>

#include <QBluetoothServiceInfo>
QTM_USE_NAMESPACE

class HIDServiceDescriptor : public QObject
{
    Q_OBJECT
public:
    explicit HIDServiceDescriptor(QObject *parent = 0);
    void registerService();
    void unregisterService();

    static const int HIDDescSize;
    static const uint HIDDesc[];

private:
    void addHIDSpecificInfo();
    QBluetoothServiceInfo serviceInfo;
};

#endif // HIDSERVICE_DESCRIPTOR_H

#endif
