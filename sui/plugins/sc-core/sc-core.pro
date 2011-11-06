#-------------------------------------------------
#
# Project created by QtCreator 2011-06-05T12:05:22
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(sc-core)
TEMPLATE = lib

INCLUDEPATH  += ../../sui
DESTDIR       = ../../sui/app/plugins/sc
CONFIG       += plugin

INCLUDEPATH += ../../core

win32 {
}
#INCLUDEPATH  += /usr/local/libSC /usr/local/libTGF
#win32:LIBS += -llibSC
unix {
    debug {
        LIBS += -lsc -lpm
    }
    release {
        LIBS += -lsc -lpm
    }
}

CONFIG (debug, debug|release) {
        DESTDIR = ../../../bin/debug/plugins/sc
} else {
        DESTDIR = ../../../bin/release/plugins/sc
}

OBJECTS_DIR = obj
MOC_DIR = moc

#DEFINES += SC_MODEL_OLD

SOURCES += \
    sccoreplugin.cpp \
    sccorememory.cpp \
    sccoreevent.cpp

HEADERS += \
    sccoreplugin.h \
    sccorememory.h \
    sccoreevent.h
