CONFIG += mobility
MOBILITY += connectivity

contains(MEEGO_EDITION,harmattan): {

    DEFINES += MEEGO_HARMATTAN
    include($$PWD/bluez/bluez.pri)
    OTHER_FILES += $$PWD/service_record.xml
    RESOURCES = $$PWD/hid.qrc
    SOURCES += \
        $$PWD/hidserv.c \ #TODO only temporarily
        $$PWD/hidservicedescriptor_bluez.cpp
    HEADERS += \
        $$PWD/hidservicedescriptor_bluez.h \
        $$PWD/hidserv.h #TODO only temporarily
    LIBS += -lbluetooth -lpthread

} else {

    HEADERS += \
        $$PWD/hidservicedescriptor.h

    SOURCES += \
        $$PWD/hidservicedescriptor.cpp
}

HEADERS += $$PWD/hidserver.h
SOURCES += $$PWD/hidserver.cpp
INCLUDEPATH += $$PWD
