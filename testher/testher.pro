TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = \
    source \
    source/io \
    source/system

SOURCES += \
    source/main.cpp \
    source/system/application.cpp \
    source/io/file.cpp \
    source/io/directory.cpp \
    source/testher.cpp

HEADERS += \
    source/system/application.h \
    source/rapidjson/allocators.h \
    source/rapidjson/document.h \
    source/rapidjson/encodedstream.h \
    source/rapidjson/encodings.h \
    source/rapidjson/filereadstream.h \
    source/rapidjson/filewritestream.h \
    source/rapidjson/memorybuffer.h \
    source/rapidjson/memorystream.h \
    source/rapidjson/pointer.h \
    source/rapidjson/prettywriter.h \
    source/rapidjson/rapidjson.h \
    source/rapidjson/reader.h \
    source/rapidjson/stringbuffer.h \
    source/rapidjson/writer.h \
    source/rapidjson/error/en.h \
    source/rapidjson/error/error.h \
    source/rapidjson/internal/biginteger.h \
    source/rapidjson/internal/diyfp.h \
    source/rapidjson/internal/dtoa.h \
    source/rapidjson/internal/ieee754.h \
    source/rapidjson/internal/itoa.h \
    source/rapidjson/internal/meta.h \
    source/rapidjson/internal/pow10.h \
    source/rapidjson/internal/stack.h \
    source/rapidjson/internal/strfunc.h \
    source/rapidjson/internal/strtod.h \
    source/rapidjson/internal/swap.h \
    source/rapidjson/msinttypes/inttypes.h \
    source/rapidjson/msinttypes/stdint.h \
    source/io/file.h \
    source/io/directory.h \
    source/testher.h
