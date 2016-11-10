#include "expression.h"

#include "iexpressionmanager.h"
#include "errorexception.h"

Expression *Expression::And(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createAnd(self, arg);
}

Expression *Expression::AttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    return IExpressionManager::instance()->createAttributeAssignment(self, name, value);
}

Expression *Expression::Block(const std::list<Expression *> &nodes) {
    return IExpressionManager::instance()->createBlock(nodes);
}

Expression *Expression::Call(const std::string &name, const std::list<Expression *> &args) {
    return IExpressionManager::instance()->createCall(name, args);
}

Expression *Expression::Constant(Object *value) {
    return IExpressionManager::instance()->createConstant(value);
}

Expression *Expression::ContextResolution(Expression *self, Expression *body, Context *context) {
    return IExpressionManager::instance()->createContextResolution(self, body, context);
}

Expression *Expression::DirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args) {
    return IExpressionManager::instance()->createDirectCall(self, name, args);
}

Expression *Expression::DynamicCall(Expression *body, const std::list<Expression *> &args) {
    return IExpressionManager::instance()->createDynamicCall(body, args);
}

Expression *Expression::Empty() {
    return IExpressionManager::instance()->createEmpty();
}

Expression *Expression::Here() {
    return IExpressionManager::instance()->createHere();
}

Expression *Expression::Identifier(const std::string &name) {
    return IExpressionManager::instance()->createIdentifier(name);
}

Expression *Expression::If(Expression *condition, Expression *body, Expression *elseBody) {
    return IExpressionManager::instance()->createIf(condition, body, elseBody);
}

Expression *Expression::Literal(const Variant &value) {
    return IExpressionManager::instance()->createLiteral(value);
}

Expression *Expression::LocalAssignment(const std::string &name, Expression *value) {
    return IExpressionManager::instance()->createLocalAssignment(name, value);
}

Expression *Expression::Loop(Expression *condition, Expression *body) {
    return IExpressionManager::instance()->createLoop(condition, body);
}

Expression *Expression::NativeCall(Object *(*f)(Context *...), const std::list<Expression *> &args) {
    return IExpressionManager::instance()->createNativeCall(f, args);
}

Expression *Expression::Not(Expression *self) {
    return IExpressionManager::instance()->createNot(self);
}

Expression *Expression::Or(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createOr(self, arg);
}

Expression *Expression::Self() {
    return IExpressionManager::instance()->createSelf();
}

Expression::~Expression() {
}

Object *Expression::eval(Context *context) {
    Object *value = 0;

    try {
        value = exec(context);
    } catch (ErrorException *e) {
        if (!e->getPosition().isValid())
            e->setPosition(getPosition());

        e->raise();
    }

    return value;
}

Position Expression::getPosition() const {
    return position;
}

void Expression::setPosition(Position position) {
    this->position = position;
}
