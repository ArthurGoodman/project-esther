TEMPLATE = lib
TARGET = esther

CONFIG += console c++11
CONFIG -= app_bundle qt

SOURCES += $$files(src/*.cpp, true)

HEADERS += \
    $$files(src/*.h, true) \
    $$files(include/*.h, true)

OTHER_FILES += $$files(src/*.def, true)

INCLUDEPATH = include src

for(file, HEADERS) DEPENDPATH += $$dirname(file)
DEPENDPATH = $$unique(DEPENDPATH)
