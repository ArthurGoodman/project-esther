#include "expressionmanager.h"

#include "andexpression.h"
#include "attributeassignmentexpression.h"
#include "blockexpression.h"
#include "constantexpression.h"
#include "contextresolutionexpression.h"
#include "emptyexpression.h"
#include "hereexpression.h"
#include "identifierexpression.h"
#include "ifexpression.h"
#include "literalexpression.h"
#include "localassignmentexpression.h"
#include "loopexpression.h"
#include "notexpression.h"
#include "orexpression.h"
#include "selfexpression.h"

Expression *ExpressionManager::createAnd(Expression *self, Expression *arg) {
    return new AndExpression(self, arg);
}

Expression *ExpressionManager::createAttributeAssignment() {
    return new AttributeAssignmentExpression(0, 0);
}

Expression *ExpressionManager::createBlock() {
    return new BlockExpression(std::list<Expression *>());
}

Expression *ExpressionManager::createConstant(Object *value) {
    return new ConstantExpression(value);
}

Expression *ExpressionManager::createContextResolution() {
    return new ContextResolutionExpression(0, 0, 0);
}

Expression *ExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::createHere() {
    return new HereExpression;
}

Expression *ExpressionManager::createIdentifier() {
    return new IdentifierExpression(0);
}

Expression *ExpressionManager::createIf() {
    return new IfExpression(0, 0, 0);
}

Expression *ExpressionManager::createLiteral(const Variant &value) {
    return new LiteralExpression(value);
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

Expression *ExpressionManager::createOr(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}
