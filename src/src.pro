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
        $$PWD/hidservicedescriptor_bluez.cpp
    HEADERS += \
        $$PWD/hidservicedescriptor_bluez.h \
    #LIBS += -lbluetooth #-lpthread

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

OTHER_FILES += \          # TODO only temporarily, for reference.
        $$PWD/hidserv.c \ # From bluemaemo app source code
        $$PWD/hidserv.h


#symbian { #TODO: Check this!
#    #we need to keep it as a.0.b in order to generate as a.b in mmp file
#    VERSION = "0.1.0"
#    TARGET.EPOCALLOWDLLDATA = 1

#    # do not freeze api-> no libs produced. Comment when freezing!
#    # run "abld freeze winscw" to create def files
#    symbian:MMP_RULES += "EXPORTUNFROZEN"

#    # workaround to generate Smart Installer via Qt SDK
#    installer.target = installer_sis
#    QMAKE_EXTRA_TARGETS += installer

#} else:unix {
#    target.path = /opt/simplestringsender/lib #TODO: temporary
#    INSTALLS += target
#}
