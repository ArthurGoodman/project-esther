TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH = source \
    source/variant \
    source/common \
    source/common/definitions \
    source/exception \
    source/expression \
    source/expression/ast \
    source/expression/debug \
    source/lexer \
    source/parser \
    source/runtime \
    source/runtime/rootclass \
    source/runtime/matcher \
    source/runtime/matcher\pattern \
    source/runtime/function \
    source/runtime/function/functionfeature \
    source/runtime/valueobject

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
    source/defaultengine.cpp \
    source/engine.cpp \
    source/exception/breakexception.cpp \
    source/exception/continueexception.cpp \
    source/exception/errorexception.cpp \
    source/exception/exception.cpp \
    source/exception/lexicalerror.cpp \
    source/exception/outofrangeexception.cpp \
    source/exception/returnexception.cpp \
    source/exception/runtimeerror.cpp \
    source/exception/syntaxerror.cpp \
    source/exception/valueexception.cpp \
    source/expression/defaultexpressionmanager.cpp \
    source/expression/expression.cpp \
    source/expression/expressionmanager.cpp \
    source/expression/ast/andexpression.cpp \
    source/expression/ast/blockexpression.cpp \
    source/expression/ast/breakexpression.cpp \
    source/expression/ast/callexpression.cpp \
    source/expression/ast/classexpression.cpp \
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
    source/expression/ast/postdecrementexpression.cpp \
    source/expression/ast/postincrementexpression.cpp \
    source/expression/ast/predecrementexpression.cpp \
    source/expression/ast/preincrementexpression.cpp \
    source/expression/ast/returnexpression.cpp \
    source/expression/ast/selfexpression.cpp \
    source/expression/ast/tupleexpression.cpp \
    source/expression/ast/whileexpression.cpp \
    source/expression/debug/debugexpression.cpp \
    source/expression/debug/debugexpressionmanager.cpp \
    source/lexer/defaultlexer.cpp \
    source/lexer/lexer.cpp \
    source/parser/defaultparser.cpp \
    source/parser/parser.cpp \
    source/runtime/call.cpp \
    source/runtime/callstack.cpp \
    source/runtime/class.cpp \
    source/runtime/context.cpp \
    source/runtime/false.cpp \
    source/runtime/module.cpp \
    source/runtime/null.cpp \
    source/runtime/object.cpp \
    source/runtime/runtime.cpp \
    source/runtime/true.cpp \
    source/runtime/tuple.cpp \
    source/runtime/function/block.cpp \
    source/runtime/function/function.cpp \
    source/runtime/function/interpretedblock.cpp \
    source/runtime/function/method.cpp \
    source/runtime/function/nativeblock.cpp \
    source/runtime/function/nativemethod.cpp \
    source/runtime/function/overloadedmethod.cpp \
    source/runtime/function/signature.cpp \
    source/runtime/valueobject/character.cpp \
    source/runtime/valueobject/float.cpp \
    source/runtime/valueobject/integer.cpp \
    source/runtime/valueobject/string.cpp \
    source/runtime/valueobject/valueobject.cpp \
    source/common/position.cpp \
    source/common/token.cpp \
    source/runtime/rootclass/booleanclass.cpp \
    source/runtime/rootclass/characterclass.cpp \
    source/runtime/rootclass/classclass.cpp \
    source/runtime/rootclass/contextclass.cpp \
    source/runtime/rootclass/floatclass.cpp \
    source/runtime/rootclass/functionclass.cpp \
    source/runtime/rootclass/integerclass.cpp \
    source/runtime/rootclass/methodclass.cpp \
    source/runtime/rootclass/nullclass.cpp \
    source/runtime/rootclass/objectclass.cpp \
    source/runtime/rootclass/rootclass.cpp \
    source/runtime/rootclass/stringclass.cpp \
    source/runtime/rootclass/tupleclass.cpp \
    source/runtime/matcher/case.cpp \
    source/exception/matchfailureexception.cpp \
    source/runtime/matcher/matcher.cpp \
    source/expression/ast/hereexpression.cpp \
    source/runtime/matcher/patternblock.cpp \
    source/runtime/matcher/pattern/pattern.cpp \
    source/runtime/matcher/pattern/wildcardpattern.cpp \
    source/runtime/interface.cpp \
    source/runtime/rootclass/interfaceclass.cpp \
    source/expression/ast/parameterexpression.cpp \
    source/runtime/function/parameter.cpp \
    source/expression/ast/functionexpression.cpp \
    source/expression/ast/methodexpression.cpp \
    source/runtime/objectcontext.cpp \
    source/expression/ast/staticexpression.cpp \
    source/runtime/function/functionfeature/functionfeature.cpp \
    source/runtime/function/functionfeature/argumentscheckerfeature.cpp \
    source/runtime/function/functionfeature/selfcheckerfeature.cpp \
    source/runtime/function/functionfeature/staticselfcheckerfeature.cpp

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
    source/defaultengine.h \
    source/engine.h \
    source/exception/breakexception.h \
    source/exception/continueexception.h \
    source/exception/errorexception.h \
    source/exception/exception.h \
    source/exception/lexicalerror.h \
    source/exception/outofrangeexception.h \
    source/exception/returnexception.h \
    source/exception/runtimeerror.h \
    source/exception/syntaxerror.h \
    source/exception/valueexception.h \
    source/expression/defaultexpressionmanager.h \
    source/expression/expression.h \
    source/expression/expressionmanager.h \
    source/expression/ast/andexpression.h \
    source/expression/ast/blockexpression.h \
    source/expression/ast/breakexpression.h \
    source/expression/ast/callexpression.h \
    source/expression/ast/classexpression.h \
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
    source/expression/ast/postdecrementexpression.h \
    source/expression/ast/postincrementexpression.h \
    source/expression/ast/predecrementexpression.h \
    source/expression/ast/preincrementexpression.h \
    source/expression/ast/returnexpression.h \
    source/expression/ast/selfexpression.h \
    source/expression/ast/tupleexpression.h \
    source/expression/ast/whileexpression.h \
    source/expression/debug/debugexpression.h \
    source/expression/debug/debugexpressionmanager.h \
    source/lexer/defaultlexer.h \
    source/lexer/lexer.h \
    source/parser/defaultparser.h \
    source/parser/parser.h \
    source/runtime/call.h \
    source/runtime/callstack.h \
    source/runtime/class.h \
    source/runtime/context.h \
    source/runtime/false.h \
    source/runtime/module.h \
    source/runtime/null.h \
    source/runtime/object.h \
    source/runtime/runtime.h \
    source/runtime/true.h \
    source/runtime/tuple.h \
    source/runtime/function/block.h \
    source/runtime/function/function.h \
    source/runtime/function/interpretedblock.h \
    source/runtime/function/method.h \
    source/runtime/function/nativeblock.h \
    source/runtime/function/nativemethod.h \
    source/runtime/function/overloadedmethod.h \
    source/runtime/function/signature.h \
    source/runtime/valueobject/character.h \
    source/runtime/valueobject/float.h \
    source/runtime/valueobject/integer.h \
    source/runtime/valueobject/string.h \
    source/runtime/valueobject/valueobject.h \
    source/common/position.h \
    source/common/token.h \
    source/common/definitions/tokens.h \
    source/runtime/rootclass/booleanclass.h \
    source/runtime/rootclass/characterclass.h \
    source/runtime/rootclass/classclass.h \
    source/runtime/rootclass/contextclass.h \
    source/runtime/rootclass/floatclass.h \
    source/runtime/rootclass/functionclass.h \
    source/runtime/rootclass/integerclass.h \
    source/runtime/rootclass/methodclass.h \
    source/runtime/rootclass/nullclass.h \
    source/runtime/rootclass/objectclass.h \
    source/runtime/rootclass/rootclass.h \
    source/runtime/rootclass/stringclass.h \
    source/runtime/rootclass/tupleclass.h \
    source/runtime/matcher/case.h \
    source/exception/matchfailureexception.h \
    source/runtime/matcher/matcher.h \
    source/expression/ast/hereexpression.h \
    source/runtime/matcher/patternblock.h \
    source/runtime/matcher/pattern/pattern.h \
    source/runtime/matcher/pattern/wildcardpattern.h \
    source/runtime/interface.h \
    source/runtime/rootclass/interfaceclass.h \
    source/expression/ast/parameterexpression.h \
    source/runtime/function/parameter.h \
    source/expression/ast/functionexpression.h \
    source/expression/ast/methodexpression.h \
    source/runtime/objectcontext.h \
    source/expression/ast/staticexpression.h \
    source/runtime/function/functionfeature/functionfeature.h \
    source/runtime/function/functionfeature/argumentscheckerfeature.h \
    source/runtime/function/functionfeature/selfcheckerfeature.h \
    source/runtime/function/functionfeature/staticselfcheckerfeature.h

OTHER_FILES += \
    README.MD \
    scripts/test.es \
    source/common/definitions/keywords.def \
    source/common/definitions/operators.def \
    source/common/definitions/othertokens.def
