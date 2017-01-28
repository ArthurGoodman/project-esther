TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += ../libesther
INCLUDEPATH += ../libesther/source
LIBS += -L../libesther/debug -lesther

SOURCES += \
    source/main.cpp

OTHER_FILES += \
    scripts/script.es \
