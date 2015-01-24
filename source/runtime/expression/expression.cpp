#include "expression.h"

#include "expressionmanager.h"

namespace esther {

ExpressionManager *Expression::manager;

void Expression::initialize() {
    manager = ExpressionManager::create();
}

void Expression::release() {
    delete manager;
}

Expression *Expression::Block(list<Expression *> nodes) {
    return manager->createBlock(nodes);
}

Expression *Expression::List(list<Expression *> nodes) {
    return manager->createList(nodes);
}

Expression *Expression::Literal(Object *value) {
    return manager->createLiteral(value);
}

Expression *Expression::Call(Expression *self, string name, list<Expression *> args) {
    return manager->createCall(self, name, args);
}

Expression *Expression::Call(Expression *self, string name, Expression *arg) {
    return manager->createCall(self, name, list<Expression *>(1, arg));
}

Expression *Expression::If(Expression *condition, Expression *body, Expression *elseBody) {
    return manager->createIf(condition, body, elseBody);
}

Expression *Expression::While(Expression *condition, Expression *body, Expression *elseBody) {
    return manager->createWhile(condition, body, elseBody);
}

Expression *Expression::For(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
    return manager->createFor(preffix, condition, suffix, body);
}

Expression *Expression::Do(Expression *body, Expression *condition) {
    return manager->createDo(body, condition);
}
}
