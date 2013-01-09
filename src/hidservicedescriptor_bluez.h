#ifndef HIDSERVICE_DESCRIPTOR_BLUEZ_H
#define HIDSERVICE_DESCRIPTOR_BLUEZ_H

#include "bluez/service_p.h"

#include <QObject>

class HIDServiceDescriptor : public QObject
{
    Q_OBJECT
public:
    explicit HIDServiceDescriptor(QObject *parent = 0);
    void registerService();
    void unregisterService();

private:
    bool registerServiceBluez();
    bool unregisterServiceBluez();
    bool ensureSdpConnection() const;

    mutable OrgBluezServiceInterface *service;
    mutable quint32 serviceRecord;
    mutable bool registered;
};

#endif // HIDSERVICE_DESCRIPTOR_BLUEZ_H
