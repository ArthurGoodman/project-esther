#include "defaultexpressionmanager.h"

#include "esther.h"
#include "emptyexpression.h"
#include "blockexpression.h"
#include "listexpression.h"
#include "literalexpression.h"
#include "orexpression.h"
#include "andexpression.h"
#include "negateexpression.h"
#include "predecrementexpression.h"
#include "preincrementexpression.h"
#include "postdecrementexpression.h"
#include "postincrementexpression.h"
#include "identifierexpression.h"
#include "identifierassignmentexpression.h"
#include "identifierdefinitionexpression.h"
#include "callexpression.h"
#include "ifexpression.h"
#include "whileexpression.h"
#include "forexpression.h"
#include "doexpression.h"
#include "contextresolutionexpression.h"
#include "classexpression.h"
#include "returnexpression.h"
#include "breakexpression.h"
#include "continueexpression.h"

namespace esther {

Expression *DefaultExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *DefaultExpressionManager::createBlock(list<Expression *> nodes) {
    return new BlockExpression(nodes);
}

Expression *DefaultExpressionManager::createList(list<Expression *> nodes) {
    return new ListExpression(nodes);
}

Expression *DefaultExpressionManager::createLiteral(Object *value) {
    return new LiteralExpression(value);
}

Expression *DefaultExpressionManager::createOr(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *DefaultExpressionManager::createAnd(Expression *self, Expression *arg) {
    return new AndExpression(self, arg);
}

Expression *DefaultExpressionManager::createNegate(Expression *self) {
    return new NegateExpression(self);
}

Expression *DefaultExpressionManager::createPreDecrement(Expression *self) {
    return new PreDecrementExpression(self);
}

Expression *DefaultExpressionManager::createPreIncrement(Expression *self) {
    return new PreIncrementExpression(self);
}

Expression *DefaultExpressionManager::createPostDecrement(Expression *self) {
    return new PostDecrementExpression(self);
}

Expression *DefaultExpressionManager::createPostIncrement(Expression *self) {
    return new PostIncrementExpression(self);
}

Expression *DefaultExpressionManager::createIdentifier(Expression *name) {
    return new IdentifierExpression(name);
}

Expression *DefaultExpressionManager::createIdentifierAssignment(Expression *name, Expression *value) {
    return new IdentifierAssignmentExpression(name, value);
}

Expression *DefaultExpressionManager::createIdentifierDefinition(Expression *name, Expression *value) {
    return new IdentifierDefinitionExpression(name, value);
}

Expression *DefaultExpressionManager::createCall(Expression *self, string name, list<Expression *> args) {
    return new CallExpression(self, name, args);
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

Expression *DefaultExpressionManager::createClassDefinition(Expression *name, Expression *superclass, Expression *body) {
    return new ClassExpression(name, superclass, body);
}

Expression *DefaultExpressionManager::createReturn(Expression *value) {
    return new ReturnExpression(value);
}

Expression *DefaultExpressionManager::createBreak(Expression *value) {
    return new BreakExpression(value);
}

Expression *DefaultExpressionManager::createContinue() {
    return new ContinueExpression;
}
}
