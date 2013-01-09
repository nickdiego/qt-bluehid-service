TEMPLATE = app
TARGET = simplestringsender

# Add more folders to ship with the application, here
qml.source = qml/simplestringsender
qml.target = qml
DEPLOYMENTFOLDERS = qml

symbian:TARGET.UID3 = 0xE96EF9BF

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices
# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable
CONFIG += mobility
MOBILITY += connectivity

# The .cpp file which was generated for your project. Feel free to hack it.
HEADERS += hidstringsender.h hidkeymapper.h
SOURCES += main.cpp hidstringsender.cpp hidkeymapper.cpp
include($$PWD/../../qt-bluehid-service.pri)

## TODO: This approach should work!
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -lbluetoothhid
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/debug/ -lbluetoothhid
#else:symbian: LIBS += -lbluetoothhid
#else:unix: LIBS += -L$$OUT_PWD/../../src/ -lbluetoothhid
#INCLUDEPATH += $$PWD/../../src
#DEPENDPATH += $$PWD/../../src
#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/release/bluetoothhid.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/debug/bluetoothhid.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../src/libbluetoothhid.a

# Please do not modify the following two lines. Required for deployment.
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
