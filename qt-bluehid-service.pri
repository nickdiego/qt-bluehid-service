CONFIG += mobility
MOBILITY += connectivity

contains(MEEGO_EDITION,harmattan) {

    DEFINES += MEEGO_HARMATTAN

    include($$PWD/src/bluez/bluez.pri)

    OTHER_FILES += $$PWD/data/service_record.xml
    RESOURCES = $$PWD/data/hid.qrc

    SOURCES += \
        $$PWD/src/hidserv.c \ #TODO only temporarily
        $$PWD/src/hidservicedescriptor_bluez.cpp

    HEADERS += \
        $$PWD/src/hidservicedescriptor_bluez.h \
        $$PWD/src/hidserv.h #TODO only temporarily

    LIBS += -lbluetooth -lpthread

} else {

    HEADERS += \
        $$PWD/src/hidservicedescriptor.h

    SOURCES += \
        $$PWD/src/hidservicedescriptor.cpp
}

HEADERS += $$PWD/src/hidserver.h
SOURCES += $$PWD/src/hidserver.cpp
INCLUDEPATH += $$PWD/src
