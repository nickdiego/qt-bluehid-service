#include "hidservicedescriptor_bluez.h"

#include "bluez/manager_p.h"
#include <QBluetoothUuid>

#define SERVICE_RECORD_FILE ":/service_record.xml"

HIDServiceDescriptor::HIDServiceDescriptor(QObject *parent) :
    QObject(parent), service(0),
    serviceRecord(0), registered(false)
{
    qDebug() << "Construct ServiceDescriptor";
}

void HIDServiceDescriptor::registerService()
{
    registerServiceBluez();
}

void HIDServiceDescriptor::unregisterService()
{
    unregisterServiceBluez();
}

bool HIDServiceDescriptor::ensureSdpConnection() const
{
    if (service)
        return true;

    OrgBluezManagerInterface manager(QLatin1String("org.bluez"), QLatin1String("/"),
                                     QDBusConnection::systemBus());

    QDBusPendingReply<QDBusObjectPath> reply = manager.FindAdapter(QLatin1String("any"));
    reply.waitForFinished();
    if (reply.isError())
        return false;

    service = new OrgBluezServiceInterface(QLatin1String("org.bluez"), reply.value().path(),
                                           QDBusConnection::systemBus());

    return true;
}

bool HIDServiceDescriptor::registerServiceBluez()
{
    if (!ensureSdpConnection())
        return false;
    QFile recordFile(SERVICE_RECORD_FILE);
    recordFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString xmlServiceRecord = recordFile.readAll();
    recordFile.close();
    //qDebug() << "SERVICE RECORD: " << xmlServiceRecord;

    if (!registered) {
        QDBusPendingReply<uint> reply = service->AddRecord(xmlServiceRecord);
        reply.waitForFinished();
        if (reply.isError())
            return false;

        serviceRecord = reply.value();
    } else {
        QDBusPendingReply<> reply = service->UpdateRecord(serviceRecord, xmlServiceRecord);
        reply.waitForFinished();
        if (reply.isError())
            return false;
    }

    qDebug() << "Bluez: Registered service!";
    registered = true;
    return true;
}

bool HIDServiceDescriptor::unregisterServiceBluez()
{
    if (!registered)
        return false;

    if (!ensureSdpConnection())
        return false;

    QDBusPendingReply<> reply = service->RemoveRecord(serviceRecord);
    reply.waitForFinished();
    if (reply.isError())
        return false;

    serviceRecord = 0;
    registered = false;
    return true;
}
