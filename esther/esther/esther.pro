TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(debug, debug|release) {
    LIBS += -L../libesther/debug
} else {
    LIBS += -L../libesther/release
}

DEPENDPATH += ../libesther
INCLUDEPATH += ../libesther/source
LIBS += -lesther

SOURCES += \
    source/main.cpp

OTHER_FILES += \
    scripts/script.es \
