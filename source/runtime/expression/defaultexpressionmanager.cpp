#include "defaultexpressionmanager.h"

#include "esther.h"
#include "blockexpression.h"
#include "listexpression.h"
#include "literalexpression.h"
#include "identifierexpression.h"
#include "identifierassignmentexpression.h"
#include "localdefinitionexpression.h"
#include "callexpression.h"
#include "cloneandcallexpression.h"
#include "ifexpression.h"
#include "whileexpression.h"
#include "forexpression.h"
#include "doexpression.h"
#include "contextresolutionexpression.h"

namespace esther {

Expression *DefaultExpressionManager::createBlock(list<Expression *> nodes) {
    return new BlockExpression(nodes);
}

Expression *DefaultExpressionManager::createList(list<Expression *> nodes) {
    return new ListExpression(nodes);
}

Expression *DefaultExpressionManager::createLiteral(Object *value) {
    return new LiteralExpression(value);
}

Expression *DefaultExpressionManager::createIdentifier(Expression *name) {
    return new IdentifierExpression(name);
}

Expression *DefaultExpressionManager::createIdentifierAssignment(Expression *name, Expression *value) {
    return new IdentifierAssignmentExpression(name, value);
}

Expression *DefaultExpressionManager::createLocalDefinition(Expression *type, Expression *name, Expression *value) {
    return new LocalDefinitionExpression(type, name, value);
}

Expression *DefaultExpressionManager::createCall(Expression *self, string name, list<Expression *> args) {
    return new CallExpression(self, name, args);
}

Expression *DefaultExpressionManager::createCloneAndCall(Expression *self, string name) {
    return new CloneAndCallExpression(self, name);
}

Expression *DefaultExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    return new IfExpression(condition, body, elseBody);
}

Expression *DefaultExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
    return new WhileExpression(condition, body, elseBody);
}

Expression *DefaultExpressionManager::createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
    return new ForExpression(preffix, condition, suffix, body);
}

Expression *DefaultExpressionManager::createDo(Expression *body, Expression *condition) {
    return new DoExpression(body, condition);
}

Expression *DefaultExpressionManager::createContextResolution(Expression *self, Expression *body) {
    return new ContextResolutionExpression(self, body);
}
}
