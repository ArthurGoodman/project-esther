#include "expression.h"

#include "iexpressionmanager.h"
#include "errorexception.h"

Expression::~Expression() {
}

Expression *Expression::Empty() {
    return IExpressionManager::instance()->createEmpty();
}

Expression *Expression::Block(list<Expression *> nodes) {
    return IExpressionManager::instance()->createBlock(nodes);
}

Expression *Expression::List(list<Expression *> nodes) {
    return IExpressionManager::instance()->createList(nodes);
}

Expression *Expression::TupleLiteral(list<Expression *> nodes) {
    return IExpressionManager::instance()->createTuple(nodes);
}

Expression *Expression::Assignment(Expression *expression, Expression *value) {
    return IExpressionManager::instance()->createAssignment(expression, value);
}

Expression *Expression::Literal(const Variant &value) {
    return IExpressionManager::instance()->createLiteral(value);
}

Expression *Expression::Constant(IObject *value) {
    return IExpressionManager::instance()->createConstant(value);
}

Expression *Expression::Or(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createOr(self, arg);
}

Expression *Expression::And(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createAnd(self, arg);
}

Expression *Expression::Negate(Expression *self) {
    return IExpressionManager::instance()->createNegate(self);
}

Expression *Expression::PreDecrement(Expression *self) {
    return IExpressionManager::instance()->createPreDecrement(self);
}

Expression *Expression::PreIncrement(Expression *self) {
    return IExpressionManager::instance()->createPreIncrement(self);
}

Expression *Expression::PostDecrement(Expression *self) {
    return IExpressionManager::instance()->createPostDecrement(self);
}

Expression *Expression::PostIncrement(Expression *self) {
    return IExpressionManager::instance()->createPostIncrement(self);
}

Expression *Expression::Identifier(Expression *name, bool dynamic) {
    return IExpressionManager::instance()->createIdentifier(name, dynamic);
}

Expression *Expression::IdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) {
    return IExpressionManager::instance()->createIdentifierDefinition(type, name, value, dynamic);
}

Expression *Expression::ParameterDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) {
    return IExpressionManager::instance()->createParameter(type, name, value, dynamic);
}

Expression *Expression::Call(Expression *self, string name, list<Expression *> args) {
    return IExpressionManager::instance()->createCall(self, name, args);
}

Expression *Expression::Call(Expression *self, string name, Expression *arg) {
    return Call(self, name, list<Expression *>(1, arg));
}

Expression *Expression::Call(Expression *self, string name) {
    return Call(self, name, list<Expression *>());
}

Expression *Expression::If(Expression *condition, Expression *body, Expression *elseBody) {
    return IExpressionManager::instance()->createIf(condition, body, elseBody);
}

Expression *Expression::While(Expression *condition, Expression *body, Expression *elseBody) {
    return IExpressionManager::instance()->createWhile(condition, body, elseBody);
}

Expression *Expression::For(Expression *param, Expression *expression, Expression *body) {
    return IExpressionManager::instance()->createFor(param, expression, body);
}

Expression *Expression::Do(Expression *body, Expression *condition) {
    return IExpressionManager::instance()->createDo(body, condition);
}

Expression *Expression::ContextResolution(Expression *self, Expression *body) {
    return IExpressionManager::instance()->createContextResolution(self, body);
}

Expression *Expression::ContextCall(Expression *self, Expression *body, list<Expression *> args) {
    return IExpressionManager::instance()->createContextCall(self, body, args);
}

Expression *Expression::ClassDefinition(Expression *name, Expression *superclass, Expression *body) {
    return IExpressionManager::instance()->createClassDefinition(name, superclass, body);
}

Expression *Expression::FunctionDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
    return IExpressionManager::instance()->createFunctionDefinition(type, name, params, body, variadic, dynamic);
}

Expression *Expression::MethodDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
    return IExpressionManager::instance()->createMethodDefinition(type, name, params, body, variadic, dynamic);
}

Expression *Expression::Return(Expression *value) {
    return IExpressionManager::instance()->createReturn(value);
}

Expression *Expression::Break(Expression *value) {
    return IExpressionManager::instance()->createBreak(value);
}

Expression *Expression::Continue() {
    return IExpressionManager::instance()->createContinue();
}

Expression *Expression::Self() {
    return IExpressionManager::instance()->createSelf();
}

Expression *Expression::Here() {
    return IExpressionManager::instance()->createHere();
}

Expression *Expression::Static(Expression *body) {
    return IExpressionManager::instance()->createStatic(body);
}

Expression *Expression::Include(Expression *fileName) {
    return IExpressionManager::instance()->createInclude(fileName);
}

Expression *Expression::ObjectLiteral(Expression *body) {
    return IExpressionManager::instance()->createObjectLiteral(body);
}

IObject *Expression::eval(Context *context) {
    IObject *value = 0;

    try {
        value = exec(context);
    } catch (ErrorException *e) {
        if (!e->getPosition().isValid())
            e->setPosition(getPosition());

        e->raise();
    }

    return value;
}

Position Expression::getPosition() {
    return position;
}

void Expression::setPosition(Position position) {
    this->position = position;
}
