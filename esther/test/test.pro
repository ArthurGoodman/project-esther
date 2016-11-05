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

INCLUDEPATH += \
    source/tests

SOURCES += \
    source/main.cpp \
    source/tests/expressiontest.cpp \
    source/tests/runtimetest.cpp \
    source/tests/varianttest.cpp

HEADERS += \
    source/tests/expressiontest.h \
    source/tests/runtimetest.h \
    source/tests/varianttest.h
