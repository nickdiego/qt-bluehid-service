TEMPLATE = lib
TARGET = bluetoothhid
CONFIG += staticlib

QT += declarative
CONFIG += mobility
MOBILITY += connectivity

contains(MEEGO_EDITION,harmattan): {

    DEFINES += MEEGO_HARMATTAN
    include($$PWD/bluez/bluez.pri)
    SOURCES += \
        $$PWD/hidserv.c \ #TODO only temporarily
        $$PWD/hidservicedescriptor_bluez.cpp
    HEADERS += \
        $$PWD/hidservicedescriptor_bluez.h \
        $$PWD/hidserv.h #TODO only temporarily
    LIBS += -lbluetooth -lpthread
    
    OTHER_FILES += $$PWD/../data/service_record.xml
    RESOURCES = $$PWD/../data/hid.qrc

} else {

    HEADERS += \
        $$PWD/hidservicedescriptor.h

    SOURCES += \
        $$PWD/hidservicedescriptor.cpp
}

HEADERS += $$PWD/hidserver.h
SOURCES += $$PWD/hidserver.cpp
INCLUDEPATH += $$PWD
