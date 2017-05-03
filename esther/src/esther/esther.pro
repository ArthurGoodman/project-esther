TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle qt

DESTDIR = ../../bin
OBJECTS_DIR = ../../bin

DEPENDPATH += ../libesther
INCLUDEPATH += ../../include
LIBS += -L../../lib -lesther

SOURCES += \
    main.cpp
