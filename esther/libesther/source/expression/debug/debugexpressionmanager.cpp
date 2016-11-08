#include "debugexpressionmanager.h"

#include "literaldebugexpression.h"
#include "utility.h"
#include "class.h"

#if DEBUG_PARSER

std::vector<const char *> DebugExpressionManager::typenames = {"Null", "Integer", "Float", "Character", "String"};

Expression *DebugExpressionManager::createAnd(Expression *self, Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("And", arguments);
}

Expression *DebugExpressionManager::createAttributeAssignment(Expression *name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << name;
    arguments << value;

    return new DebugExpression("AttributeAssignment", arguments);
}

Expression *DebugExpressionManager::createBlock(const std::list<Expression *> &nodes) {
    std::list<DebugExpression *> arguments;

    for (Expression *e : nodes)
        arguments << e;

    return new DebugExpression("Block", arguments);
}

Expression *DebugExpressionManager::createCall(Expression *name, const std::list<Expression *> &args) {
    std::list<DebugExpression *> arguments, callArguments;

    arguments << name;

    for (Expression *arg : args)
        callArguments << arg;

    arguments << new DebugExpression("List", callArguments);

    return new DebugExpression("Call", arguments);
}

Expression *DebugExpressionManager::createConstant(Object *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(value->getClass()->getName(), value->toString());

    return new DebugExpression("Constant", arguments);
}

Expression *DebugExpressionManager::createContextResolution(Expression *self, Expression *body, Context *context) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << body;
    arguments << literal("Context", Utility::toString((void *)context));

    return new DebugExpression("ContextResolution", arguments);
}

Expression *DebugExpressionManager::createDirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args) {
    std::list<DebugExpression *> arguments, callArguments;

    arguments << self;
    arguments << literal(typenames[Variant::String], name);

    for (Expression *arg : args)
        callArguments << arg;

    arguments << new DebugExpression("List", callArguments);

    return new DebugExpression("DirectCall", arguments);
}

Expression *DebugExpressionManager::createDynamicCall(Expression *body, const std::list<Expression *> &args) {
    std::list<DebugExpression *> arguments, callArguments;

    arguments << body;

    for (Expression *arg : args)
        callArguments << arg;

    arguments << new DebugExpression("List", callArguments);

    return new DebugExpression("DynamicCall", arguments);
}

Expression *DebugExpressionManager::createEmpty() {
    return new DebugExpression("Empty");
}

Expression *DebugExpressionManager::createHere() {
    return new DebugExpression("Here");
}

Expression *DebugExpressionManager::createIdentifier(Expression *name) {
    std::list<DebugExpression *> arguments;

    arguments << name;

    return new DebugExpression("Identifier", arguments);
}

Expression *DebugExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    std::list<DebugExpression *> arguments;

    arguments << condition;
    arguments << body;
    arguments << elseBody;

    return new DebugExpression("If", arguments);
}

Expression *DebugExpressionManager::createLiteral(const Variant &value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[value.getType()], value.toString());

    return new DebugExpression("Literal", arguments);
}

Expression *DebugExpressionManager::createLocalAssignment(Expression *name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << name;
    arguments << value;

    return new DebugExpression("LocalAssignment", arguments);
}

Expression *DebugExpressionManager::createLoop(Expression *condition, Expression *body) {
    std::list<DebugExpression *> arguments;

    arguments << condition;
    arguments << body;

    return new DebugExpression("Loop", arguments);
}

Expression *DebugExpressionManager::createNot(Expression *self) {
    std::list<DebugExpression *> arguments;

    arguments << self;

    return new DebugExpression("Not", arguments);
}

Expression *DebugExpressionManager::createOr(Expression *self, Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("Or", arguments);
}

Expression *DebugExpressionManager::createSelf() {
    return new DebugExpression("Self");
}

DebugExpression *DebugExpressionManager::literal(const std::string &type, const std::string &value) {
    return new LiteralDebugExpression("<" + type + " : \"" + value + "\">");
}

#endif
