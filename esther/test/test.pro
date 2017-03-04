TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += ../libesther
INCLUDEPATH += ../libesther/src

DEPENDPATH += ../../../unit
INCLUDEPATH += ../../../unit

win32 {
LIBS += -L../libesther/release -lesther
LIBS += -L../../../unit/release -lunit
}

unix {
LIBS += -L../libesther -lesther
LIBS += -L../../../unit -lunit
}

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
