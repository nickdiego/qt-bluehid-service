TEMPLATE = app
TARGET = simplestringsender

qml.source = qml/simplestringsender
qml.target = qml
DEPLOYMENTFOLDERS = qml

symbian:TARGET.UID3 = 0xE96EF9BF
symbian:TARGET.CAPABILITY += NetworkServices

CONFIG += qdeclarative-boostable mobility
MOBILITY += connectivity

HEADERS += hidstringsender.h hidkeymapper.h
SOURCES += main.cpp hidstringsender.cpp hidkeymapper.cpp
#include($$PWD/../../qt-bluehid-service.pri)

# TODO: This approach should work!
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -lbluetoothhid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/debug/ -lbluetoothhid
else:symbian: LIBS += -lbluetoothhid
else:unix: LIBS += -L$$OUT_PWD/../../src/ -lbluetoothhid

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/release/bluetoothhid.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/debug/bluetoothhid.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../src/libbluetoothhid.a

#qtbluehidlib.files = \
#    $$OUT_PWD/../../src/libbluetoothhid.so      \
#    $$OUT_PWD/../../src/libbluetoothhid.so.1    \
#    $$OUT_PWD/../../src/libbluetoothhid.so.1.0  \
#    $$OUT_PWD/../../src/libbluetoothhid.so.1.0.0
#qtbluehidlib.path = /opt/simplestringsender/lib

#INSTALLS += qtbluehidlib
#QMAKE_LFLAGS += -Wl,--rpath=/opt/simplestringsender/lib

include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
