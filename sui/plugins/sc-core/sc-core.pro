#-------------------------------------------------
#
# Project created by QtCreator 2011-06-05T12:05:22
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(sc-core)
TEMPLATE = lib

INCLUDEPATH  += ../../sui
DESTDIR       = ../../sui/plugins/sc
CONFIG       += plugin

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
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}

MOC_DIR = build/moc

#DEFINES += SC_MODEL_OLD

SOURCES += \
    sccoreplugin.cpp \
    sccorememory.cpp \
    sccoreevent.cpp

HEADERS += \
    sccoreplugin.h \
    sccorememory.h \
    sccoreevent.h
