TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = \
    source \
    source\common\
    source\common\definitions \
    source\exception \
    source\expression \
    source\lexer \
    source\parser \
    source\runtime

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
    source/common/common.cpp \
    source/lexer/ilexer.cpp \
    source/parser/iparser.cpp \
    source/runtime/object.cpp \
    source/parser/parser.cpp \
    source/lexer/lexer.cpp \
    source/expression/expression.cpp \
    source/engine.cpp \
    source/runtime/runtime.cpp \
    source/runtime/class.cpp \
    source/exception/breakexception.cpp \
    source/exception/continueexception.cpp \
    source/exception/errorexception.cpp \
    source/exception/exception.cpp \
    source/exception/lexicalerror.cpp \
    source/exception/returnexception.cpp \
    source/exception/runtimeerror.cpp \
    source/exception/syntaxerror.cpp \
    source/exception/valueexception.cpp

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
    source/common/definitions/tokens.h \
    source/lexer/ilexer.h \
    source/parser/iparser.h \
    source/runtime/object.h \
    source/parser/parser.h \
    source/lexer/lexer.h \
    source/expression/expression.h \
    source/engine.h \
    source/runtime/runtime.h \
    source/runtime/class.h \
    source/exception/breakexception.h \
    source/exception/continueexception.h \
    source/exception/errorexception.h \
    source/exception/exception.h \
    source/exception/lexicalerror.h \
    source/exception/returnexception.h \
    source/exception/runtimeerror.h \
    source/exception/syntaxerror.h \
    source/exception/valueexception.h

OTHER_FILES += \
    scripts/script.es \
    source/common/definitions/keywords.def \
    source/common/definitions/operators.def \
    source/common/definitions/othertokens.def
