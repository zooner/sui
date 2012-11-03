#-------------------------------------------------
#
# Project created by QtCreator 2011-06-04T23:28:59
#
#-------------------------------------------------

QT       += core gui

TARGET = sui
TEMPLATE = app

PRECOMPILED_HEADER = suiprecompiled.h

INCLUDEPATH += ../
PRECOMPILED_HEADER = precompiled.h

CONFIG (debug, debug|release) {
        DESTDIR = ../../bin/debug
} else {
        DESTDIR = ../../bin/release
}

unix {
    POST_TARGETDEPS += $$DESTDIR/libsuiCore.so
    LIBS += $$DESTDIR/libsuiCore.so
    QMAKE_RPATHDIR += $$DESTDIR
}

OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    precompiled.h
