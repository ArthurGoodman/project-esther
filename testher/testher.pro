TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = src

SOURCES += \
    src/main.cpp \
    src/system/application.cpp \
    src/io/file.cpp \
    src/io/directory.cpp \
    src/testher.cpp

HEADERS += \
    src/system/application.h \
    src/rapidjson/allocators.h \
    src/rapidjson/document.h \
    src/rapidjson/encodedstream.h \
    src/rapidjson/encodings.h \
    src/rapidjson/filereadstream.h \
    src/rapidjson/filewritestream.h \
    src/rapidjson/memorybuffer.h \
    src/rapidjson/memorystream.h \
    src/rapidjson/pointer.h \
    src/rapidjson/prettywriter.h \
    src/rapidjson/rapidjson.h \
    src/rapidjson/reader.h \
    src/rapidjson/stringbuffer.h \
    src/rapidjson/writer.h \
    src/rapidjson/error/en.h \
    src/rapidjson/error/error.h \
    src/rapidjson/internal/biginteger.h \
    src/rapidjson/internal/diyfp.h \
    src/rapidjson/internal/dtoa.h \
    src/rapidjson/internal/ieee754.h \
    src/rapidjson/internal/itoa.h \
    src/rapidjson/internal/meta.h \
    src/rapidjson/internal/pow10.h \
    src/rapidjson/internal/stack.h \
    src/rapidjson/internal/strfunc.h \
    src/rapidjson/internal/strtod.h \
    src/rapidjson/internal/swap.h \
    src/rapidjson/msinttypes/inttypes.h \
    src/rapidjson/msinttypes/stdint.h \
    src/io/file.h \
    src/io/directory.h \
    src/testher.h
