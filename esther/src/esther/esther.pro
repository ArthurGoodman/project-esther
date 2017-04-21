TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle at

DESTDIR = ../../bin
OBJECTS_DIR = ../../bin

DEPENDPATH += ../libesther
INCLUDEPATH += ../../include

LIBS += -L../../lib
LIBS += -lesther

SOURCES += \
    main.cpp
