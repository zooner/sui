#-------------------------------------------------
#
# Project created by QtCreator 2011-11-06T12:42:09
#
#-------------------------------------------------

QT       += gui

TARGET = suiCore
TEMPLATE = lib
VERSION = 0.1.0

DEFINES += SUICORE_LIBRARY

OBJECTS_DIR = obj
MOC_DIR = moc

CONFIG (debug, debug|release) {
        DESTDIR = ../../bin/debug
} else {
        DESTDIR = ../../bin/release
}

SOURCES += suicore.cpp \
    suischelper.cpp \
    suiroot.cpp \
    suiprecompiled.cpp \
    suipluginmanager.cpp \
    suikpm.cpp \
    suiknowbase.cpp \
    suicomponentsmanager.cpp \
    kpm/suioperation.cpp \
    kpm/suimainwindowremoveoperation.cpp \
    kpm/suimainwindowaddoperation.cpp

HEADERS += suicore.h\
        suiCore_global.h \
    suischelper.h \
    suiroot.h \
    suiprecompiled.h \
    suipluginmanager.h \
    suikpm.h \
    suiknowbase.h \
    suiconfig.h \
    suicomponentsmanager.h \
    kpm/suioperation.h \
    kpm/suimainwindowremoveoperation.h \
    kpm/suimainwindowaddoperation.h

