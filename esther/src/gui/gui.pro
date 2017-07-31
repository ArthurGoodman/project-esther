TARGET = libgui

TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../../lib

INCLUDEPATH += ../../include
LIBS += -L../../lib -llibesther

SOURCES += gui.c
