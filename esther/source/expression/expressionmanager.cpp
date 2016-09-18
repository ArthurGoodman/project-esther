#include "expressionmanager.h"

#include "andexpression.h"
#include "attributeassignmentexpression.h"
#include "blockexpression.h"
#include "classexpression.h"
#include "constantexpression.h"
#include "contextresolutionexpression.h"
#include "emptyexpression.h"
#include "functionexpression.h"
#include "identifierexpression.h"
#include "ifexpression.h"
#include "literalexpression.h"
#include "localassignmentexpression.h"
#include "loopexpression.h"
#include "notexpression.h"
#include "orexpression.h"
#include "selfexpression.h"

Expression *ExpressionManager::createAnd() {
    return new AndExpression(0, 0);
}

Expression *ExpressionManager::createAttributeAssignment() {
    return new AttributeAssignmentExpression(0, 0);
}

Expression *ExpressionManager::createBlock() {
    return new BlockExpression(std::list<Expression *>());
}

Expression *ExpressionManager::createClass() {
    return new ClassExpression;
}

Expression *ExpressionManager::createConstant() {
    return new ConstantExpression(0);
}

Expression *ExpressionManager::createContextResolution() {
    return new ContextResolutionExpression(0, 0, 0);
}

Expression *ExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::createFunction() {
    return new FunctionExpression;
}

Expression *ExpressionManager::createIdentifier() {
    return new IdentifierExpression(0);
}

Expression *ExpressionManager::createIf() {
    return new IfExpression(0, 0, 0);
}

Expression *ExpressionManager::createLiteral() {
    return new LiteralExpression(Variant());
}

Expression *ExpressionManager::createLocalAssignment() {
    return new LocalAssignmentExpression(0, 0);
}

Expression *ExpressionManager::createLoop() {
    return new LoopExpression(0, 0);
}

Expression *ExpressionManager::createNot() {
    return new NotExpression(0);
}

Expression *ExpressionManager::createOr() {
    return new OrExpression(0, 0);
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}
