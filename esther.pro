TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = source \
    source/exception \
    source/lexer \
    source/parser \
    source/runtime \
    source/runtime/function \
    source/expression \
    source/expression/ast \
    source/expression/debug \
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
    source/runtime/class.cpp \
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
    source/runtime/function/method.cpp \
    source/runtime/function/overloadedmethod.cpp \
    source/runtime/context.cpp \
    source/runtime/module.cpp \
    source/lexer/token.cpp \
    source/lexer/position.cpp \
    source/common/io.cpp \
    source/common/logger.cpp \
    source/runtime/valueobject.cpp \
    source/variant/variantprivate.cpp \
    source/runtime/true.cpp \
    source/runtime/false.cpp \
    source/runtime/null.cpp \
    source/expression/defaultexpressionmanager.cpp \
    source/expression/expression.cpp \
    source/expression/expressionmanager.cpp \
    source/expression/debug/debugexpression.cpp \
    source/expression/debug/debugexpressionmanager.cpp \
    source/expression/ast/andexpression.cpp \
    source/expression/ast/blockexpression.cpp \
    source/expression/ast/breakexpression.cpp \
    source/expression/ast/callexpression.cpp \
    source/expression/ast/classexpression.cpp \
    source/expression/ast/cloneandcallexpression.cpp \
    source/expression/ast/contextresolutionexpression.cpp \
    source/expression/ast/continueexpression.cpp \
    source/expression/ast/doexpression.cpp \
    source/expression/ast/emptyexpression.cpp \
    source/expression/ast/forexpression.cpp \
    source/expression/ast/identifierassignmentexpression.cpp \
    source/expression/ast/identifierdefinitionexpression.cpp \
    source/expression/ast/identifierexpression.cpp \
    source/expression/ast/ifexpression.cpp \
    source/expression/ast/listexpression.cpp \
    source/expression/ast/literalexpression.cpp \
    source/expression/ast/negateexpression.cpp \
    source/expression/ast/orexpression.cpp \
    source/expression/ast/returnexpression.cpp \
    source/expression/ast/whileexpression.cpp \
    source/runtime/function/block.cpp \
    source/common/utility.cpp \
    source/esther.cpp \
    source/runtime/runtime.cpp

HEADERS += \
    source/variant/charvariant.h \
    source/variant/floatvariant.h \
    source/variant/integervariant.h \
    source/variant/nullvariant.h \
    source/variant/stringvariant.h \
    source/variant/variant.h \
    source/variant/variantprivate.h \
    source/runtime/object.h \
    source/runtime/class.h \
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
    source/runtime/function/method.h \
    source/runtime/function/overloadedmethod.h \
    source/runtime/context.h \
    source/runtime/module.h \
    source/lexer/token.h \
    source/lexer/position.h \
    source/common/common.h \
    source/common/io.h \
    source/common/logger.h \
    source/common/debug.h \
    source/runtime/valueobject.h \
    source/runtime/true.h \
    source/runtime/false.h \
    source/runtime/null.h \
    source/expression/defaultexpressionmanager.h \
    source/expression/expression.h \
    source/expression/expressionmanager.h \
    source/expression/debug/debugexpression.h \
    source/expression/debug/debugexpressionmanager.h \
    source/expression/ast/andexpression.h \
    source/expression/ast/blockexpression.h \
    source/expression/ast/breakexpression.h \
    source/expression/ast/callexpression.h \
    source/expression/ast/classexpression.h \
    source/expression/ast/cloneandcallexpression.h \
    source/expression/ast/contextresolutionexpression.h \
    source/expression/ast/continueexpression.h \
    source/expression/ast/doexpression.h \
    source/expression/ast/emptyexpression.h \
    source/expression/ast/forexpression.h \
    source/expression/ast/identifierassignmentexpression.h \
    source/expression/ast/identifierdefinitionexpression.h \
    source/expression/ast/identifierexpression.h \
    source/expression/ast/ifexpression.h \
    source/expression/ast/listexpression.h \
    source/expression/ast/literalexpression.h \
    source/expression/ast/negateexpression.h \
    source/expression/ast/orexpression.h \
    source/expression/ast/returnexpression.h \
    source/expression/ast/whileexpression.h \
    source/runtime/function/block.h \
    source/common/utility.h \
    source/esther.h \
    source/runtime/runtime.h

OTHER_FILES += \
    README.MD \
    scripts/test.es
