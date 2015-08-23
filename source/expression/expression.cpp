#include "expression.h"

#include "expressionmanager.h"

ExpressionManager *Expression::manager;

void Expression::initialize() {
    manager = ExpressionManager::create();
}

void Expression::release() {
    delete manager;
}

Expression *Expression::Empty() {
    return manager->createEmpty();
}

Expression *Expression::Block(list<Expression *> nodes) {
    return manager->createBlock(nodes);
}

Expression *Expression::List(list<Expression *> nodes) {
    return manager->createList(nodes);
}

Expression *Expression::TupleLiteral(list<Expression *> nodes) {
    return manager->createTuple(nodes);
}

Expression *Expression::Literal(Object *value) {
    return manager->createLiteral(value);
}

Expression *Expression::Or(Expression *self, Expression *arg) {
    return manager->createOr(self, arg);
}

Expression *Expression::And(Expression *self, Expression *arg) {
    return manager->createAnd(self, arg);
}

Expression *Expression::Negate(Expression *self) {
    return manager->createNegate(self);
}

Expression *Expression::PreDecrement(Expression *self) {
    return manager->createPreDecrement(self);
}

Expression *Expression::PreIncrement(Expression *self) {
    return manager->createPreIncrement(self);
}

Expression *Expression::PostDecrement(Expression *self) {
    return manager->createPostDecrement(self);
}

Expression *Expression::PostIncrement(Expression *self) {
    return manager->createPostIncrement(self);
}

Expression *Expression::Identifier(Expression *name) {
    return manager->createIdentifier(name);
}

Expression *Expression::IdentifierAssignment(Expression *name, Expression *value) {
    return manager->createIdentifierAssignment(name, value);
}

Expression *Expression::IdentifierDefinition(Expression *type, Expression *name, Expression *value) {
    return manager->createIdentifierDefinition(type, name, value);
}

Expression *Expression::ParameterDefinition(Expression *type, Expression *name, Expression *value) {
    return manager->createParameter(type, name, value);
}

Expression *Expression::Call(Expression *self, string name, list<Expression *> args) {
    return manager->createCall(self, name, args);
}

Expression *Expression::Call(Expression *self, string name, Expression *arg) {
    return Call(self, name, list<Expression *>(1, arg));
}

Expression *Expression::Call(Expression *self, string name) {
    return Call(self, name, list<Expression *>());
}

Expression *Expression::If(Expression *condition, Expression *body, Expression *elseBody) {
    return manager->createIf(condition, body, elseBody);
}

Expression *Expression::While(Expression *condition, Expression *body, Expression *elseBody) {
    return manager->createWhile(condition, body, elseBody);
}

//Expression *Expression::For(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
//    return manager->createFor(preffix, condition, suffix, body);
//}

Expression *Expression::Do(Expression *body, Expression *condition) {
    return manager->createDo(body, condition);
}

Expression *Expression::ContextResolution(Expression *self, Expression *body) {
    return manager->createContextResolution(self, body);
}

Expression *Expression::ClassDefinition(Expression *name, Expression *superclass, Expression *body) {
    return manager->createClassDefinition(name, superclass, body);
}

Expression *Expression::FunctionDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic) {
    return manager->createFunctionDefinition(type, name, params, body, variadic);
}

Expression *Expression::MethodDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic) {
    return manager->createMethodDefinition(type, name, params, body, variadic);
}

Expression *Expression::Return(Expression *value) {
    return manager->createReturn(value);
}

Expression *Expression::Break(Expression *value) {
    return manager->createBreak(value);
}

Expression *Expression::Continue() {
    return manager->createContinue();
}

Expression *Expression::Self() {
    return manager->createSelf();
}

Expression *Expression::Here() {
    return manager->createHere();
}

Expression *Expression::Static(Expression *body) {
    return manager->createStatic(body);
}

Expression *Expression::Include(Expression *fileName) {
    return manager->createInclude(fileName);
}

Expression *Expression::ObjectLiteral(Expression *body) {
    return manager->createObjectLiteral(body);
}
