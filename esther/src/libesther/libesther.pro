TEMPLATE = lib
TARGET = esther

CONFIG += console c++11 c11
CONFIG -= app_bundle qt

DESTDIR = ../../lib
OBJECTS_DIR = ../../lib

SOURCES += \
    $$files(*.cpp, true) \
    $$files(*.c, true)

HEADERS += \
    $$files(*.h, true) \
    $$files(../../include/*.h, true)

OTHER_FILES += \
    $$files(*.def, true)

INCLUDEPATH = ../../include

for(file, HEADERS) DEPENDPATH += $$dirname(file)
DEPENDPATH = $$unique(DEPENDPATH)
