TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += ../libesther
INCLUDEPATH += ../libesther/source
LIBS += -L../libesther/release -lesther

DEPENDPATH += ../../../unit
INCLUDEPATH += ../../../unit
LIBS += -L../../../unit/release -lunit

SOURCES += \
    source/main.cpp \
    source/expressiontest.cpp

HEADERS += \
    source/expressiontest.h
