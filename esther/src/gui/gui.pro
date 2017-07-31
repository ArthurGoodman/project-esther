TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

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

SOURCES += gui.c
