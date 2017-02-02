#include "debugexpressionmanager.h"

#include "expression/debug/literaldebugexpression.h"
#include "common/utility.h"
#include "runtime/class.h"

#if DEBUG_PARSER

std::vector<const char *> DebugExpressionManager::typenames = { "Null", "Character", "Integer", "Float", "String" };

Expression *DebugExpressionManager::createAnd(Expression *self, Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("And", arguments);
}

Expression *DebugExpressionManager::createAssignment(const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
    arguments << value;

    return new DebugExpression("Assignment", arguments);
}

Expression *DebugExpressionManager::createAttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << literal(typenames[Variant::String], name);
    arguments << value;

    return new DebugExpression("AttributeAssignment", arguments);
}

Expression *DebugExpressionManager::createAttribute(Expression *self, const std::string &name) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << literal(typenames[Variant::String], name);

    return new DebugExpression("Attribute", arguments);
}

Expression *DebugExpressionManager::createBlock(const std::list<Expression *> &nodes) {
    std::list<DebugExpression *> arguments;

    for (Expression *e : nodes)
        arguments << e;

    return new DebugExpression("Block", arguments);
}

Expression *DebugExpressionManager::createCall(Expression *f, Expression *self, int args) {
    std::list<DebugExpression *> arguments;

    arguments << f;
    arguments << self;
    arguments << literal(typenames[Variant::Integer], Utility::toString(args));

    return new DebugExpression("Call", arguments);
}

Expression *DebugExpressionManager::createClassDefinition(const std::string &name, Expression *superclass) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
    arguments << superclass;

    return new DebugExpression("ClassDefinition", arguments);
}

Expression *DebugExpressionManager::createConstant(Object *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(value->getClass()->getName(), value->toString());

    return new DebugExpression("Constant", arguments);
}

Expression *DebugExpressionManager::createContextResolution(Expression *self, Expression *body, Expression *here) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << body;

    if (here != nullptr)
        arguments << here;

    return new DebugExpression("ContextResolution", arguments);
}

Expression *DebugExpressionManager::createEmpty() {
    return new DebugExpression("Empty");
}

Expression *DebugExpressionManager::createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) {
    std::list<DebugExpression *> arguments, parameters;

    arguments << literal(typenames[Variant::String], name);

    for (auto &param : params)
        parameters << literal(typenames[Variant::String], param);

    arguments << new DebugExpression("List", parameters);

    arguments << body;

    return new DebugExpression("FunctionDefinition", arguments);
}

Expression *DebugExpressionManager::createHere() {
    return new DebugExpression("Here");
}

Expression *DebugExpressionManager::createIdentifier(const std::string &name) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);

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

Expression *DebugExpressionManager::createLocalAssignment(const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
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

Expression *DebugExpressionManager::createPop(int count) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::Integer], Utility::toString(count));

    return new DebugExpression("Pop", arguments);
}

Expression *DebugExpressionManager::createPush(Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << arg;

    return new DebugExpression("Push", arguments);
}

Expression *DebugExpressionManager::createSelf() {
    return new DebugExpression("Self");
}

Expression *DebugExpressionManager::createStack(int index) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::Integer], Utility::toString(index));

    return new DebugExpression("Stack", arguments);
}

DebugExpression *DebugExpressionManager::literal(const std::string &type, const std::string &value) {
    return new LiteralDebugExpression("<" + type + " : \"" + value + "\">");
}

#endif
