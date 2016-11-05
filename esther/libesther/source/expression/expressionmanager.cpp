#include "expressionmanager.h"

#include "andexpression.h"
#include "attributeassignmentexpression.h"
#include "blockexpression.h"
#include "callexpression.h"
#include "constantexpression.h"
#include "contextcallepression.h"
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

Expression *ExpressionManager::createAttributeAssignment(Expression *name, Expression *value) {
    return new AttributeAssignmentExpression(name, value);
}

Expression *ExpressionManager::createBlock(const std::list<Expression *> &nodes) {
    return new BlockExpression(nodes);
}

Expression *ExpressionManager::createCall() {
    return new CallExpression(0, {});
}

Expression *ExpressionManager::createConstant(Object *value) {
    return new ConstantExpression(value);
}

Expression *ExpressionManager::createContextCall() {
    return new ContextCallEpression(0, 0, {});
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

Expression *ExpressionManager::createIdentifier(Expression *name) {
    return new IdentifierExpression(name);
}

Expression *ExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    return new IfExpression(condition, body, elseBody);
}

Expression *ExpressionManager::createLiteral(const Variant &value) {
    return new LiteralExpression(value);
}

Expression *ExpressionManager::createLocalAssignment(Expression *name, Expression *value) {
    return new LocalAssignmentExpression(name, value);
}

Expression *ExpressionManager::createLoop() {
    return new LoopExpression(0, 0);
}

Expression *ExpressionManager::createNot(Expression *self) {
    return new NotExpression(self);
}

Expression *ExpressionManager::createOr(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}
