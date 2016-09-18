#include "debugexpressionmanager.h"

#include "common.h"
#include "debugexpression.h"
#include "class.h"
#include "runtime.h"

#if DEBUG_PARSER

Expression *DebugExpressionManager::createAnd() {
    return new DebugExpression("And");
}

Expression *DebugExpressionManager::createAttributeAssignment() {
    return new DebugExpression("AttributeAssignment");
}

Expression *DebugExpressionManager::createBlock() {
    return new DebugExpression("Block");
}

Expression *DebugExpressionManager::createClass() {
    return new DebugExpression("Class");
}

Expression *DebugExpressionManager::createConstant() {
    return new DebugExpression("Constant");
}

Expression *DebugExpressionManager::createContextResolution() {
    return new DebugExpression("ContextResolution");
}

Expression *DebugExpressionManager::createEmpty() {
    return new DebugExpression("Empty");
}

Expression *DebugExpressionManager::createFunction() {
    return new DebugExpression("Function");
}

Expression *DebugExpressionManager::createIf() {
    return new DebugExpression("If");
}

Expression *DebugExpressionManager::createLiteral() {
    return new DebugExpression("Literal");
}

Expression *DebugExpressionManager::createLocalAssignment() {
    return new DebugExpression("LocalAssignment");
}

Expression *DebugExpressionManager::createLoop() {
    return new DebugExpression("Loop");
}

Expression *DebugExpressionManager::createNot() {
    return new DebugExpression("Not");
}

Expression *DebugExpressionManager::createOr() {
    return new DebugExpression("Or");
}

Expression *DebugExpressionManager::createSelf() {
    return new DebugExpression("Self");
}

#endif
