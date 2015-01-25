#include "defaultexpressionmanager.h"

#include "esther.h"
#include "blockexpression.h"
#include "listexpression.h"
#include "literalexpression.h"

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
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createIdentifierAssignment(Expression *name, Expression *value) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createLocalDefinition(Expression *type, Expression *name, Expression *value) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createCall(Expression *self, string name, list<Expression *> args) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createCloneAndCall(Expression *self, string name) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createDo(Expression *body, Expression *condition) {
    return new LiteralExpression(Esther::getNull());
}

Expression *DefaultExpressionManager::createContextResolution(Expression *self, Expression *body) {
    return new LiteralExpression(Esther::getNull());
}
}
