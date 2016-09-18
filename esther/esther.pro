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
    source\expression\ast \
    source\expression\debug \
    source\parser \
    source\runtime \
    source\variant

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
    source/exception/valueexception.cpp \
    source/expression/expressionmanager.cpp \
    source/expression/iexpressionmanager.cpp \
    source/expression/debug/debugexpression.cpp \
    source/expression/debug/debugexpressionmanager.cpp \
    source/variant/charvariant.cpp \
    source/variant/floatvariant.cpp \
    source/variant/integervariant.cpp \
    source/variant/nullvariant.cpp \
    source/variant/stringvariant.cpp \
    source/variant/variant.cpp \
    source/variant/variantprivate.cpp \
    source/expression/ast/emptyexpression.cpp \
    source/runtime/context.cpp \
    source/runtime/false.cpp \
    source/runtime/function.cpp \
    source/runtime/null.cpp \
    source/runtime/true.cpp \
    source/runtime/valueobject/character.cpp \
    source/runtime/valueobject/float.cpp \
    source/runtime/valueobject/integer.cpp \
    source/runtime/valueobject/stringvalueobject.cpp \
    source/runtime/valueobject/valueobject.cpp \
    source/expression/ast/andexpression.cpp \
    source/expression/ast/attributeassignmentexpression.cpp \
    source/expression/ast/blockexpression.cpp \
    source/expression/ast/callexpression.cpp \
    source/expression/ast/classexpression.cpp \
    source/expression/ast/constantexpression.cpp \
    source/expression/ast/contextresolutionexpression.cpp \
    source/expression/ast/functionexpression.cpp \
    source/expression/ast/ifexpression.cpp \
    source/expression/ast/literalexpression.cpp \
    source/expression/ast/localassignmentexpression.cpp \
    source/expression/ast/loopexpression.cpp \
    source/expression/ast/notexpression.cpp \
    source/expression/ast/orexpression.cpp \
    source/expression/ast/selfexpression.cpp

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
    source/exception/valueexception.h \
    source/expression/expressionmanager.h \
    source/expression/iexpressionmanager.h \
    source/expression/debug/debugexpression.h \
    source/expression/debug/debugexpressionmanager.h \
    source/variant/charvariant.h \
    source/variant/floatvariant.h \
    source/variant/integervariant.h \
    source/variant/nullvariant.h \
    source/variant/stringvariant.h \
    source/variant/variant.h \
    source/variant/variantprivate.h \
    source/expression/ast/emptyexpression.h \
    source/runtime/context.h \
    source/runtime/false.h \
    source/runtime/function.h \
    source/runtime/null.h \
    source/runtime/true.h \
    source/runtime/valueobject/character.h \
    source/runtime/valueobject/float.h \
    source/runtime/valueobject/integer.h \
    source/runtime/valueobject/stringvalueobject.h \
    source/runtime/valueobject/valueobject.h \
    source/expression/ast/andexpression.h \
    source/expression/ast/attributeassignmentexpression.h \
    source/expression/ast/blockexpression.h \
    source/expression/ast/callexpression.h \
    source/expression/ast/classexpression.h \
    source/expression/ast/constantexpression.h \
    source/expression/ast/contextresolutionexpression.h \
    source/expression/ast/functionexpression.h \
    source/expression/ast/ifexpression.h \
    source/expression/ast/literalexpression.h \
    source/expression/ast/localassignmentexpression.h \
    source/expression/ast/loopexpression.h \
    source/expression/ast/notexpression.h \
    source/expression/ast/orexpression.h \
    source/expression/ast/selfexpression.h

OTHER_FILES += \
    scripts/script.es \
    source/common/definitions/keywords.def \
    source/common/definitions/operators.def \
    source/common/definitions/othertokens.def
