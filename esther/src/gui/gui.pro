TEMPLATE = lib
CONFIG += c++11

QT += core gui widgets

DESTDIR = ../../lib

INCLUDEPATH += ../../include

unix {
TARGET = gui
LIBS += -L../../lib -lesther
}

win32 {
TARGET = libgui
LIBS += -L../../lib -llibesther
}

SOURCES += \
    gui.cpp
