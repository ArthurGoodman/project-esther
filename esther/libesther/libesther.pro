TEMPLATE = lib
TARGET = esther

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -masm=intel

INCLUDEPATH = src

SOURCES += \
    src/common/bytearray.cpp \
    src/common/io.cpp \
    src/common/position.cpp \
    src/common/source.cpp \
    src/common/token.cpp \
    src/common/utility.cpp \
    src/lexer/ilexer.cpp \
    src/parser/iparser.cpp \
    src/runtime/object.cpp \
    src/parser/parser.cpp \
    src/lexer/lexer.cpp \
    src/expression/expression.cpp \
    src/runtime/class.cpp \
    src/exception/breakexception.cpp \
    src/exception/continueexception.cpp \
    src/exception/errorexception.cpp \
    src/exception/exception.cpp \
    src/exception/lexicalerror.cpp \
    src/exception/returnexception.cpp \
    src/exception/runtimeerror.cpp \
    src/exception/syntaxerror.cpp \
    src/exception/valueexception.cpp \
    src/expression/expressionmanager.cpp \
    src/expression/debug/debugexpression.cpp \
    src/expression/debug/debugexpressionmanager.cpp \
    src/expression/ast/emptyexpression.cpp \
    src/runtime/context.cpp \
    src/runtime/false.cpp \
    src/runtime/null.cpp \
    src/runtime/true.cpp \
    src/expression/ast/andexpression.cpp \
    src/expression/ast/attributeassignmentexpression.cpp \
    src/expression/ast/blockexpression.cpp \
    src/expression/ast/constantexpression.cpp \
    src/expression/ast/contextresolutionexpression.cpp \
    src/expression/ast/identifierexpression.cpp \
    src/expression/ast/ifexpression.cpp \
    src/expression/ast/literalexpression.cpp \
    src/expression/ast/loopexpression.cpp \
    src/expression/ast/notexpression.cpp \
    src/expression/ast/orexpression.cpp \
    src/expression/ast/selfexpression.cpp \
    src/runtime/interpretedfunction.cpp \
    src/runtime/function.cpp \
    src/runtime/nativefunction.cpp \
    src/expression/ast/hereexpression.cpp \
    src/variant/charvariant.cpp \
    src/variant/floatvariant.cpp \
    src/variant/integervariant.cpp \
    src/variant/nullvariant.cpp \
    src/variant/stringvariant.cpp \
    src/variant/variant.cpp \
    src/variant/variantprivate.cpp \
    src/runtime/rootclass/booleanclass.cpp \
    src/runtime/rootclass/nullclass.cpp \
    src/runtime/valueobject.cpp \
    src/runtime/rootclass/integerclass.cpp \
    src/runtime/rootclass/characterclass.cpp \
    src/runtime/rootclass/floatclass.cpp \
    src/runtime/rootclass/stringclass.cpp \
    src/runtime/rootclass/objectclass.cpp \
    src/runtime/rootclass/classclass.cpp \
    src/runtime/rootclass/functionclass.cpp \
    src/runtime/rootclass/rootclass.cpp \
    src/expression/debug/literaldebugexpression.cpp \
    src/expression/ast/classdefinitionexpression.cpp \
    src/expression/ast/functiondefinitionexpression.cpp \
    src/runtime/rootclass/numericclass.cpp \
    src/expression/ast/assignmentexpression.cpp \
    src/expression/ast/attributeexpression.cpp \
    src/expression/ast/localassignmentexpression.cpp \
    src/expression/ast/callexpression.cpp \
    src/estherstaticinterface.cpp \
    src/runtime/esther.cpp \
    src/expression/ast/popexpression.cpp \
    src/expression/ast/pushexpression.cpp \
    src/expression/ast/stackexpression.cpp \
    src/memory/managedobject.cpp \
    src/memory/markcompactmemorymanager.cpp \
    src/memory/memorymanager.cpp \
    src/memory/nomemorymanager.cpp \
    src/memory/pointer.cpp \
    src/memory/semispacememorymanager.cpp \
    src/memory/staticobject.cpp \
    src/collections/array.cpp \
    src/collections/hashmap.cpp \
    src/collections/list.cpp \
    src/collections/map.cpp \
    src/collections/sherwoodmap.cpp \
    src/common/log.cpp

HEADERS += \
    src/common/bytearray.h \
    src/common/common.h \
    src/common/io.h \
    src/common/position.h \
    src/common/source.h \
    src/common/token.h \
    src/common/utility.h \
    src/common/definitions/tokens.h \
    src/lexer/ilexer.h \
    src/parser/iparser.h \
    src/runtime/object.h \
    src/parser/parser.h \
    src/lexer/lexer.h \
    src/expression/expression.h \
    src/runtime/class.h \
    src/exception/breakexception.h \
    src/exception/continueexception.h \
    src/exception/errorexception.h \
    src/exception/exception.h \
    src/exception/lexicalerror.h \
    src/exception/returnexception.h \
    src/exception/runtimeerror.h \
    src/exception/syntaxerror.h \
    src/exception/valueexception.h \
    src/expression/expressionmanager.h \
    src/expression/debug/debugexpression.h \
    src/expression/debug/debugexpressionmanager.h \
    src/variant/charvariant.h \
    src/variant/floatvariant.h \
    src/variant/integervariant.h \
    src/variant/nullvariant.h \
    src/variant/stringvariant.h \
    src/variant/variant.h \
    src/variant/variantprivate.h \
    src/expression/ast/emptyexpression.h \
    src/runtime/context.h \
    src/runtime/false.h \
    src/runtime/null.h \
    src/runtime/true.h \
    src/expression/ast/andexpression.h \
    src/expression/ast/attributeassignmentexpression.h \
    src/expression/ast/blockexpression.h \
    src/expression/ast/callexpression.h \
    src/expression/ast/constantexpression.h \
    src/expression/ast/contextresolutionexpression.h \
    src/expression/ast/hereexpression.h \
    src/expression/ast/identifierexpression.h \
    src/expression/ast/ifexpression.h \
    src/expression/ast/literalexpression.h \
    src/expression/ast/loopexpression.h \
    src/expression/ast/notexpression.h \
    src/expression/ast/orexpression.h \
    src/expression/ast/selfexpression.h \
    src/runtime/interpretedfunction.h \
    src/runtime/function.h \
    src/runtime/nativefunction.h \
    src/runtime/rootclass/booleanclass.h \
    src/runtime/rootclass/nullclass.h \
    src/runtime/valueobject.h \
    src/runtime/rootclass/integerclass.h \
    src/runtime/rootclass/characterclass.h \
    src/runtime/rootclass/floatclass.h \
    src/runtime/rootclass/stringclass.h \
    src/runtime/rootclass/objectclass.h \
    src/runtime/rootclass/classclass.h \
    src/runtime/rootclass/functionclass.h \
    src/runtime/rootclass/rootclass.h \
    src/expression/debug/literaldebugexpression.h \
    src/expression/ast/nativecallexpression.h \
    src/expression/ast/cachedexpression.h \
    src/expression/ast/classdefinitionexpression.h \
    src/expression/ast/functiondefinitionexpression.h \
    src/runtime/rootclass/numericclass.h \
    src/expression/ast/assignmentexpression.h \
    src/expression/ast/attributeexpression.h \
    src/expression/ast/localassignmentexpression.h \
    src/expression/ast/callexpression.h \
    src/estherstaticinterface.h \
    src/runtime/esther.h \
    src/expression/ast/popexpression.h \
    src/expression/ast/pushexpression.h \
    src/expression/ast/stackexpression.h \
    src/memory/managedobject.h \
    src/memory/markcompactmemorymanager.h \
    src/memory/memorymanager.h \
    src/memory/nomemorymanager.h \
    src/memory/pointer.h \
    src/memory/semispacememorymanager.h \
    src/memory/staticobject.h \
    src/collections/array.h \
    src/collections/hashmap.h \
    src/collections/list.h \
    src/collections/map.h \
    src/collections/sherwoodmap.h \
    src/common/config.h \
    src/common/log.h

OTHER_FILES += \
    src/common/definitions/keywords.def \
    src/common/definitions/operators.def \
    src/common/definitions/othertokens.def
