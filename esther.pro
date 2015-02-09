TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = source \
    source/variant \
    source/common \
    source/esther \
    source/esther/exception \
    source/esther/expression \
    source/esther/expression/ast \
    source/esther/expression/debug \
    source/esther/lexer \
    source/esther/parser \
    source/esther/runtime \
    source/esther/runtime/function

SOURCES += \
    source/esther.cpp \
    source/main.cpp \
    source/common/io.cpp \
    source/common/logger.cpp \
    source/common/utility.cpp \
    source/variant/charvariant.cpp \
    source/variant/floatvariant.cpp \
    source/variant/integervariant.cpp \
    source/variant/nullvariant.cpp \
    source/variant/stringvariant.cpp \
    source/variant/variant.cpp \
    source/variant/variantprivate.cpp \
    source/esther/exception/breakexception.cpp \
    source/esther/exception/continueexception.cpp \
    source/esther/exception/errorexception.cpp \
    source/esther/exception/exception.cpp \
    source/esther/exception/lexicalerror.cpp \
    source/esther/exception/returnexception.cpp \
    source/esther/exception/runtimeerror.cpp \
    source/esther/exception/syntaxerror.cpp \
    source/esther/exception/valueexception.cpp \
    source/esther/expression/defaultexpressionmanager.cpp \
    source/esther/expression/expression.cpp \
    source/esther/expression/expressionmanager.cpp \
    source/esther/expression/ast/andexpression.cpp \
    source/esther/expression/ast/blockexpression.cpp \
    source/esther/expression/ast/breakexpression.cpp \
    source/esther/expression/ast/callexpression.cpp \
    source/esther/expression/ast/classexpression.cpp \
    source/esther/expression/ast/cloneandcallexpression.cpp \
    source/esther/expression/ast/contextresolutionexpression.cpp \
    source/esther/expression/ast/continueexpression.cpp \
    source/esther/expression/ast/doexpression.cpp \
    source/esther/expression/ast/emptyexpression.cpp \
    source/esther/expression/ast/forexpression.cpp \
    source/esther/expression/ast/identifierassignmentexpression.cpp \
    source/esther/expression/ast/identifierdefinitionexpression.cpp \
    source/esther/expression/ast/identifierexpression.cpp \
    source/esther/expression/ast/ifexpression.cpp \
    source/esther/expression/ast/listexpression.cpp \
    source/esther/expression/ast/literalexpression.cpp \
    source/esther/expression/ast/negateexpression.cpp \
    source/esther/expression/ast/orexpression.cpp \
    source/esther/expression/ast/returnexpression.cpp \
    source/esther/expression/ast/whileexpression.cpp \
    source/esther/expression/debug/debugexpression.cpp \
    source/esther/expression/debug/debugexpressionmanager.cpp \
    source/esther/lexer/defaultlexer.cpp \
    source/esther/lexer/lexer.cpp \
    source/esther/lexer/position.cpp \
    source/esther/lexer/token.cpp \
    source/esther/parser/defaultparser.cpp \
    source/esther/parser/parser.cpp \
    source/esther/runtime/class.cpp \
    source/esther/runtime/context.cpp \
    source/esther/runtime/false.cpp \
    source/esther/runtime/module.cpp \
    source/esther/runtime/null.cpp \
    source/esther/runtime/object.cpp \
    source/esther/runtime/runtime.cpp \
    source/esther/runtime/true.cpp \
    source/esther/runtime/valueobject.cpp \
    source/esther/runtime/function/block.cpp \
    source/esther/runtime/function/function.cpp \
    source/esther/runtime/function/method.cpp \
    source/esther/runtime/function/overloadedmethod.cpp \
    source/esther/defaultengine.cpp \
    source/esther/engine.cpp

HEADERS += \
    source/esther.h \
    source/common/common.h \
    source/common/debug.h \
    source/common/io.h \
    source/common/logger.h \
    source/common/utility.h \
    source/variant/charvariant.h \
    source/variant/floatvariant.h \
    source/variant/integervariant.h \
    source/variant/nullvariant.h \
    source/variant/stringvariant.h \
    source/variant/variant.h \
    source/variant/variantprivate.h \
    source/esther/exception/breakexception.h \
    source/esther/exception/continueexception.h \
    source/esther/exception/errorexception.h \
    source/esther/exception/exception.h \
    source/esther/exception/lexicalerror.h \
    source/esther/exception/returnexception.h \
    source/esther/exception/runtimeerror.h \
    source/esther/exception/syntaxerror.h \
    source/esther/exception/valueexception.h \
    source/esther/expression/defaultexpressionmanager.h \
    source/esther/expression/expression.h \
    source/esther/expression/expressionmanager.h \
    source/esther/expression/ast/andexpression.h \
    source/esther/expression/ast/blockexpression.h \
    source/esther/expression/ast/breakexpression.h \
    source/esther/expression/ast/callexpression.h \
    source/esther/expression/ast/classexpression.h \
    source/esther/expression/ast/cloneandcallexpression.h \
    source/esther/expression/ast/contextresolutionexpression.h \
    source/esther/expression/ast/continueexpression.h \
    source/esther/expression/ast/doexpression.h \
    source/esther/expression/ast/emptyexpression.h \
    source/esther/expression/ast/forexpression.h \
    source/esther/expression/ast/identifierassignmentexpression.h \
    source/esther/expression/ast/identifierdefinitionexpression.h \
    source/esther/expression/ast/identifierexpression.h \
    source/esther/expression/ast/ifexpression.h \
    source/esther/expression/ast/listexpression.h \
    source/esther/expression/ast/literalexpression.h \
    source/esther/expression/ast/negateexpression.h \
    source/esther/expression/ast/orexpression.h \
    source/esther/expression/ast/returnexpression.h \
    source/esther/expression/ast/whileexpression.h \
    source/esther/expression/debug/debugexpression.h \
    source/esther/expression/debug/debugexpressionmanager.h \
    source/esther/lexer/defaultlexer.h \
    source/esther/lexer/lexer.h \
    source/esther/lexer/position.h \
    source/esther/lexer/token.h \
    source/esther/parser/defaultparser.h \
    source/esther/parser/parser.h \
    source/esther/runtime/class.h \
    source/esther/runtime/context.h \
    source/esther/runtime/false.h \
    source/esther/runtime/module.h \
    source/esther/runtime/null.h \
    source/esther/runtime/object.h \
    source/esther/runtime/runtime.h \
    source/esther/runtime/true.h \
    source/esther/runtime/valueobject.h \
    source/esther/runtime/function/block.h \
    source/esther/runtime/function/function.h \
    source/esther/runtime/function/method.h \
    source/esther/runtime/function/overloadedmethod.h \
    source/esther/defaultengine.h \
    source/esther/engine.h

OTHER_FILES += \
    README.MD \
    scripts/test.es
