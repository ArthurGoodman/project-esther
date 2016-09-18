#include "expressionmanager.h"

#include "andexpression.h"
#include "attributeassignmentexpression.h"
#include "blockexpression.h"
#include "classexpression.h"
#include "constantexpression.h"
#include "contextresolutionexpression.h"
#include "emptyexpression.h"
#include "functionexpression.h"
#include "ifexpression.h"
#include "literalexpression.h"
#include "localassignmentexpression.h"
#include "loopexpression.h"
#include "notexpression.h"
#include "orexpression.h"
#include "selfexpression.h"

Expression *ExpressionManager::createAnd() {
    return new AndExpression;
}

Expression *ExpressionManager::createAttributeAssignment() {
    return new AttributeAssignmentExpression;
}

Expression *ExpressionManager::createBlock() {
    return new BlockExpression;
}

Expression *ExpressionManager::createClass() {
    return new ClassExpression;
}

Expression *ExpressionManager::createConstant() {
    return new ConstantExpression;
}

Expression *ExpressionManager::createContextResolution() {
    return new ContextResolutionExpression;
}

Expression *ExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::createFunction() {
    return new FunctionExpression;
}

Expression *ExpressionManager::createIf() {
    return new IfExpression;
}

Expression *ExpressionManager::createLiteral() {
    return new LiteralExpression;
}

Expression *ExpressionManager::createLocalAssignment() {
    return new LocalAssignmentExpression;
}

Expression *ExpressionManager::createLoop() {
    return new LoopExpression;
}

Expression *ExpressionManager::createNot() {
    return new NotExpression;
}

Expression *ExpressionManager::createOr() {
    return new OrExpression;
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}
