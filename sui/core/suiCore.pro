#-------------------------------------------------
#
# Project created by QtCreator 2011-11-06T12:42:09
#
#-------------------------------------------------

QT       -= gui

TARGET = suiCore
TEMPLATE = lib

TARGETDEPS += suiCore

DEFINES += SUICORE_LIBRARY

CONFIG (debug, debug|release) {
        OBJECTS_DIR = ../sui/build/debug
} else {
        OBJECTS_DIR = ../sui/build/release
}

MOC_DIR = build/moc

SOURCES += suicore.cpp

HEADERS += suicore.h\
        suiCore_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE26CEA28
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = suiCore.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
