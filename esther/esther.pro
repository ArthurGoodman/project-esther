TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = \
    source \
    source\common\
    source\common\definitions

SOURCES += \
    source/main.cpp \
    source/esther.cpp \
    source/common/bytearray.cpp \
    source/common/io.cpp \
    source/common/logger.cpp \
    source/common/position.cpp \
    source/common/source.cpp \
    source/common/token.cpp \
    source/common/utility.cpp \
    source/common/common.cpp

HEADERS += \
    source/esther.h \
    source/common/bytearray.h \
    source/common/common.h \
    source/common/debug.h \
    source/common/io.h \
    source/common/logger.h \
    source/common/position.h \
    source/common/source.h \
    source/common/token.h \
    source/common/utility.h \
    source/common/definitions/tokens.h

OTHER_FILES += \
    scripts/script.es \
    source/common/definitions/keywords.def \
    source/common/definitions/operators.def \
    source/common/definitions/othertokens.def
