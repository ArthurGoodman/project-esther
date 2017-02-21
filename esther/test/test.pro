TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += ../libesther
INCLUDEPATH += ../libesther/src
LIBS += -L../libesther/release -lesther

DEPENDPATH += ../../../unit
INCLUDEPATH += ../../../unit
LIBS += -L../../../unit/release -lunit

INCLUDEPATH += \
    src/tests

SOURCES += \
    src/main.cpp \
    src/tests/expressiontest.cpp \
    src/tests/runtimetest.cpp \
    src/tests/varianttest.cpp

HEADERS += \
    src/tests/expressiontest.h \
    src/tests/runtimetest.h \
    src/tests/varianttest.h
