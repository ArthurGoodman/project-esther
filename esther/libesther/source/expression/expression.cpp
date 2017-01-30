#include "expression.h"

#include "esther.h"
#include "iexpressionmanager.h"
#include "errorexception.h"

Expression *Expression::And(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createAnd(self, arg);
}

Expression *Expression::Assignment(const std::string &name, Expression *value) {
    return IExpressionManager::instance()->createAssignment(name, value);
}

Expression *Expression::AttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    return IExpressionManager::instance()->createAttributeAssignment(self, name, value);
}

Expression *Expression::Attribute(Expression *self, const std::string &name) {
    return IExpressionManager::instance()->createAttribute(self, name);
}

Expression *Expression::Block(const std::list<Expression *> &nodes) {
    return IExpressionManager::instance()->createBlock(nodes);
}

Expression *Expression::Call(Expression *f, Expression *self, int args) {
    return IExpressionManager::instance()->createCall(f, self, args);
}

Expression *Expression::ClassDefinition(const std::string &name, Expression *superclass) {
    return IExpressionManager::instance()->createClassDefinition(name, superclass);
}

Expression *Expression::Constant(Pointer<Object> value) {
    return IExpressionManager::instance()->createConstant(value);
}

Expression *Expression::ContextResolution(Expression *self, Expression *body, Expression *here) {
    return IExpressionManager::instance()->createContextResolution(self, body, here);
}

Expression *Expression::Empty() {
    return IExpressionManager::instance()->createEmpty();
}

Expression *Expression::FunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) {
    return IExpressionManager::instance()->createFunctionDefinition(name, params, body);
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

Expression *Expression::Not(Expression *self) {
    return IExpressionManager::instance()->createNot(self);
}

Expression *Expression::Or(Expression *self, Expression *arg) {
    return IExpressionManager::instance()->createOr(self, arg);
}

Expression *Expression::Pop(int count) {
    return IExpressionManager::instance()->createPop(count);
}

Expression *Expression::Push(Expression *arg) {
    return IExpressionManager::instance()->createPush(arg);
}

Expression *Expression::Self() {
    return IExpressionManager::instance()->createSelf();
}

Expression *Expression::Stack(int index) {
    return IExpressionManager::instance()->createStack(index);
}

Expression::~Expression() {
}

Pointer<Object> Expression::eval(Esther *esther) {
    Object *value = nullptr;

    try {
        value = exec(esther);
    } catch (ErrorException *e) {
        if (!e->getPosition().isValid())
            e->setPosition(getPosition());

        e->raise();
    }

    esther->setReg(value);

    return value;
}

Position Expression::getPosition() const {
    return position;
}

void Expression::setPosition(Position position) {
    this->position = position;
}
