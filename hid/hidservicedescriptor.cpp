#include "hidservicedescriptor.h"

#include <QBluetoothUuid>

/** HID Descriptor
 * Similar example here:
 * http://www.developer.nokia.com/Community/Wiki/Bluetooth_HID_profile_(client_device)
 *
 * more details, please see HID spec
 * http://bluetooth.org
 **/
const int HIDServiceDescriptor::HIDDescSize = 119;
const uint HIDServiceDescriptor::HIDDesc[HIDServiceDescriptor::HIDDescSize] = {
        // Keyboard descriptor
        0x05, 0x01,
        0x09, 0x06,
        0xa1, 0x01,
        0x85, 0x01,
        0x05, 0x07,
        0x19, 0xe0,
        0x29, 0xe7,
        0x15, 0x00,
        0x25, 0x01,
        0x75, 0x01,
        0x95, 0x08,
        0x81, 0x02,
        0x95, 0x01,
        0x75, 0x08,
        0x81, 0x03,
        0x95, 0x05,
        0x75, 0x01,
        0x05, 0x08,
        0x19, 0x01,
        0x29, 0x05,
        0x91, 0x02,
        0x95, 0x01,
        0x75, 0x03,
        0x91, 0x03,
        0x95, 0x06,
        0x75, 0x08,
        0x15, 0x00,
        0x25, 0x65,
        0x05, 0x07,
        0x19, 0x00,
        0x29, 0x65,
        0x81, 0x00,
        0xc0,
        // Mouse descriptor
        0x05, 0x01,
        0x09, 0x02,
        0xa1, 0x01,
        0x85, 0x02,
        0x09, 0x01,
        0xa1, 0x00,
        0x05, 0x09,
        0x19, 0x01,
        0x29, 0x03,
        0x15, 0x00,
        0x25, 0x01,
        0x75, 0x01,
        0x95, 0x03,
        0x81, 0x02,
        0x75, 0x05,
        0x95, 0x01,
        0x81, 0x01,
        0x05, 0x01,
        0x09, 0x30,
        0x09, 0x31,
        0x09, 0x38,
        0x15, 0x81,
        0x25, 0x7f,
        0x75, 0x08,
        0x95, 0x03,
        0x81, 0x06,
        0xc0,
        0xc0
};

HIDServiceDescriptor::HIDServiceDescriptor(QObject *parent) :
    QObject(parent)
{
}

void HIDServiceDescriptor::registerService()
{
    registerServiceGeneric();
}

void HIDServiceDescriptor::unregisterService()
{
    unregisterServiceGeneric();
}

void HIDServiceDescriptor::registerServiceGeneric() {
    QBluetoothUuid serviceId(QBluetoothUuid::HumanInterfaceDeviceService);

    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceRecordHandle, (uint)0x0001000e);

    //! [Class Uuuid must contain at least 1 entry]
    QBluetoothServiceInfo::Sequence classId;
    classId << QVariant::fromValue(serviceId);
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
    //! [Class Uuuid must contain at least 1 entry]


    //! [Service name, description and provider]
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("NokiaKeyboard"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                             tr("Nokia phone as a bluetooth keyboard"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("INdT"));
    //! [Service name, description and provider]

    //! [Service UUID set]
    serviceInfo.setServiceUuid(serviceId);
    //! [Service UUID set]

    //! [Service Discoverability]
    serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                             QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    //! [Service Discoverability]

    //! [Protocol descriptor list]
    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap))
             << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Hidp));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Hidp));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);
    //! [Protocol descriptor list]

    //! [LanguageBaseAttributeID list 0x0006]
    QBluetoothServiceInfo::Sequence languageAttributes;
    languageAttributes << QVariant::fromValue((quint16) 0x656e)
                       << QVariant::fromValue((quint16) 0x006a)
                       << QVariant::fromValue((quint16) 0x0100);
    serviceInfo.setAttribute(0x0006, languageAttributes);
    //! [LanguageBaseAttributeID list 0x0006]

    //! [BluetoothProfileDescriptor list 0x0009]
    QBluetoothServiceInfo::Sequence profileDescriptorList;
    profileDescriptorList << QVariant::fromValue(serviceId)
                       << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    serviceInfo.setAttribute(0x0009, profileDescriptorList);
    //! [BluetoothProfileDescriptor list 0x0009]

    addHIDSpecificInfo();

    Q_ASSERT(serviceInfo.isComplete());
    Q_ASSERT(serviceInfo.isValid());


    qDebug() << "SERVICE INFO: " << serviceInfo;
    serviceInfo.registerService();

    Q_ASSERT(serviceInfo.isRegistered());
}

void HIDServiceDescriptor::unregisterServiceGeneric() {
    serviceInfo.unregisterService();

    Q_ASSERT(serviceInfo.isRegistered() == false);
}

void HIDServiceDescriptor::addHIDSpecificInfo() {
    serviceInfo.setAttribute(0x0202, QVariant::fromValue((quint8) 0xc0));
    serviceInfo.setAttribute(0x0203, QVariant::fromValue((quint8) 0x30));
    serviceInfo.setAttribute(0x0204, QVariant::fromValue(false));
    serviceInfo.setAttribute(0x0205, QVariant::fromValue(true));

    // 0x0206 HIDDescriptorList ??
    // FIXME: How to do this with Qt Mobility ?? at least for Symbian
    QByteArray rawHidDescriptor(HIDServiceDescriptor::HIDDesc, HIDServiceDescriptor::HIDDescSize);
    QString hidDescriptor(rawHidDescriptor);

    QBluetoothServiceInfo::Sequence hidDescriptorList;
    hidDescriptorList << QVariant::fromValue((quint8) 0x22)
                      << hidDescriptor;
    serviceInfo.setAttribute(0x0206, hidDescriptorList);

    QBluetoothServiceInfo::Sequence hidLanguageList;
    hidLanguageList << QVariant::fromValue((quint16) 0x0409)
                    << QVariant::fromValue((quint16) 0x0100);
    serviceInfo.setAttribute(0x0207, hidLanguageList);


    serviceInfo.setAttribute(0x0208, QVariant::fromValue(false));
    serviceInfo.setAttribute(0x0209, QVariant::fromValue(true));
    serviceInfo.setAttribute(0x020a, QVariant::fromValue(false));
    serviceInfo.setAttribute(0x020b, QVariant::fromValue((quint16) 0x0100));
    serviceInfo.setAttribute(0x020d, QVariant::fromValue(false));
    serviceInfo.setAttribute(0x020e, QVariant::fromValue(true));
}
