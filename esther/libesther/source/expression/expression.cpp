#include "expression.h"

#include "iexpressionmanager.h"
#include "errorexception.h"

Expression *Expression::And(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createAnd(self, arg);
}

Expression *Expression::AttributeAssignment() {
    return IExpressionManager::instance()->createAttributeAssignment();
}

Expression *Expression::Block() {
    return IExpressionManager::instance()->createBlock();
}

Expression *Expression::Constant(Object *value) {
    return IExpressionManager::instance()->createConstant(value);
}

Expression *Expression::ContextResolution() {
    return IExpressionManager::instance()->createContextResolution();
}

Expression *Expression::Empty() {
    return IExpressionManager::instance()->createEmpty();
}

Expression *Expression::Here() {
    return IExpressionManager::instance()->createHere();
}

Expression *Expression::If() {
    return IExpressionManager::instance()->createIf();
}

Expression *Expression::Literal(const Variant &value) {
    return IExpressionManager::instance()->createLiteral(value);
}

Expression *Expression::LocalAssignment() {
    return IExpressionManager::instance()->createLocalAssignment();
}

Expression *Expression::Loop() {
    return IExpressionManager::instance()->createLoop();
}

Expression *Expression::Not() {
    return IExpressionManager::instance()->createNot();
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

Position Expression::getPosition() {
    return position;
}

void Expression::setPosition(Position position) {
    this->position = position;
}
