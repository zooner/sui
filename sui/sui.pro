#-------------------------------------------------
#
# Project created by QtCreator 2011-06-04T23:28:59
#
#-------------------------------------------------

QT       += core gui

TARGET = sui
TEMPLATE = app

PRECOMPILED_HEADER = suiprecompiled.h
SUBDIRS = plugins/sc-core \
           plugins/scg

CONFIG += ordered

CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}

MOC_DIR = build/moc

SOURCES += main.cpp\
        mainwindow.cpp \
    suiroot.cpp \
    suicomponentsmanager.cpp \
    suipluginmanager.cpp \
    suiprecompiled.cpp \
    suiknowbase.cpp \
    suischelper.cpp \
    suikpm.cpp \
    kpm/suioperation.cpp \
    kpm/suimainwindowaddoperation.cpp \
    kpm/suimainwindowremoveoperation.cpp

HEADERS  += mainwindow.h \
    interfaces/UiRoot.h \
    interfaces/UiObjects.h \
    interfaces/UiComponents.h \
    interfaces/ScMemory.h \
    suiroot.h \
    suicomponentsmanager.h \
    interfaces/UiCompManager.h \
    suipluginmanager.h \
    interfaces/UiPlugins.h \
    suiprecompiled.h \
    suiknowbase.h \
    interfaces/ScHelper.h \
    suischelper.h \
    interfaces/_utils.h \
    suikpm.h \
    kpm/suioperation.h \
    kpm/suimainwindowaddoperation.h \
    suiconfig.h \
    kpm/suimainwindowremoveoperation.h
