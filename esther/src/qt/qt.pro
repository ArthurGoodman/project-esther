TEMPLATE = lib
CONFIG += c++11

QT += core gui widgets

DESTDIR = ../../lib

INCLUDEPATH += ../../include

unix {
TARGET = qt
LIBS += -L../../lib -lesther
}

win32 {
TARGET = libqt
LIBS += -L../../lib -llibesther
}

SOURCES += \
    qt.cpp
