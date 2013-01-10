TEMPLATE = subdirs
SUBDIRS = simple-string-sender

symbian {
    # workaround to generate Smart Installer via Qt SDK
    installer.target = installer_sis
    QMAKE_EXTRA_TARGETS += installer
} else:unix {
    target.path = /opt/simplestringsender/lib
    INSTALLS += target
}
