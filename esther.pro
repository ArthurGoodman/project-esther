TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = source \
    source/exception \
    source/lexer \
    source/parser \
    source/runtime \
    source/runtime/expression \
    source/runtime/expression/ast \
    source/runtime/function \
    source/variant \
    source/common

SOURCES += \
    source/main.cpp \
    source/variant/charvariant.cpp \
    source/variant/floatvariant.cpp \
    source/variant/integervariant.cpp \
    source/variant/nullvariant.cpp \
    source/variant/stringvariant.cpp \
    source/variant/variant.cpp \
    source/runtime/object.cpp \
    source/scriptengine.cpp \
    source/estherengine.cpp \
    source/runtime/class.cpp \
    source/runtime/garbagecollector.cpp \
    source/lexer/lexer.cpp \
    source/parser/parser.cpp \
    source/lexer/defaultlexer.cpp \
    source/parser/defaultparser.cpp \
    source/exception/exception.cpp \
    source/exception/breakexception.cpp \
    source/exception/continueexception.cpp \
    source/exception/errorexception.cpp \
    source/exception/lexicalerror.cpp \
    source/exception/returnexception.cpp \
    source/exception/runtimeerror.cpp \
    source/exception/syntaxerror.cpp \
    source/exception/valueexception.cpp \
    source/runtime/function/function.cpp \
    source/runtime/function/interpretedfunction.cpp \
    source/runtime/function/interpretedmethod.cpp \
    source/runtime/function/method.cpp \
    source/runtime/function/nativemethod.cpp \
    source/runtime/function/overloadedmethod.cpp \
    source/runtime/expression/expression.cpp \
    source/runtime/expression/expressionmanager.cpp \
    source/runtime/expression/defaultexpressionmanager.cpp \
    source/runtime/context.cpp \
    source/runtime/module.cpp \
    source/lexer/token.cpp \
    source/lexer/position.cpp \
    source/esther.cpp \
    source/common/io.cpp \
    source/common/logger.cpp

HEADERS += \
    source/variant/charvariant.h \
    source/variant/floatvariant.h \
    source/variant/integervariant.h \
    source/variant/nullvariant.h \
    source/variant/stringvariant.h \
    source/variant/variant.h \
    source/variant/variantprivate.h \
    source/runtime/object.h \
    source/scriptengine.h \
    source/estherengine.h \
    source/runtime/class.h \
    source/runtime/garbagecollector.h \
    source/lexer/lexer.h \
    source/parser/parser.h \
    source/lexer/defaultlexer.h \
    source/parser/defaultparser.h \
    source/exception/exception.h \
    source/exception/breakexception.h \
    source/exception/continueexception.h \
    source/exception/errorexception.h \
    source/exception/lexicalerror.h \
    source/exception/returnexception.h \
    source/exception/runtimeerror.h \
    source/exception/syntaxerror.h \
    source/exception/valueexception.h \
    source/runtime/function/function.h \
    source/runtime/function/interpretedfunction.h \
    source/runtime/function/interpretedmethod.h \
    source/runtime/function/method.h \
    source/runtime/function/nativemethod.h \
    source/runtime/function/overloadedmethod.h \
    source/runtime/expression/expression.h \
    source/runtime/expression/expressionmanager.h \
    source/runtime/expression/defaultexpressionmanager.h \
    source/runtime/context.h \
    source/runtime/module.h \
    source/lexer/token.h \
    source/lexer/position.h \
    source/esther.h \
    source/common/common.h \
    source/common/io.h \
    source/common/logger.h

OTHER_FILES += \
    README.MD \
    scripts/test.es
