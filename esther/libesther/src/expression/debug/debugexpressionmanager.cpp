#include "expression/debug/debugexpressionmanager.h"

#include "common/utility.h"
#include "variant/variant.h"
#include "runtime/class.h"
#include "expression/debug/debugexpression.h"
#include "expression/debug/literaldebugexpression.h"

#ifdef DEBUG_EXPRESSION

namespace es {

std::vector<const char *> DebugExpressionManager::typenames = { "Null", "Character", "Integer", "Float", "String" };

Expression *DebugExpressionManager::And(Expression *self, Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("And", arguments);
}

Expression *DebugExpressionManager::Assignment(const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
    arguments << value;

    return new DebugExpression("Assignment", arguments);
}

Expression *DebugExpressionManager::AttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << literal(typenames[Variant::String], name);
    arguments << value;

    return new DebugExpression("AttributeAssignment", arguments);
}

Expression *DebugExpressionManager::Attribute(Expression *self, const std::string &name) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << literal(typenames[Variant::String], name);

    return new DebugExpression("Attribute", arguments);
}

Expression *DebugExpressionManager::Block(const std::list<Expression *> &nodes) {
    std::list<DebugExpression *> arguments;

    for (Expression *e : nodes)
        if (static_cast<DebugExpression *>(e)->name == "Block") {
            arguments.insert(arguments.end(), static_cast<DebugExpression *>(e)->args.begin(), static_cast<DebugExpression *>(e)->args.end());
            static_cast<DebugExpression *>(e)->args.clear();
            delete e;
        } else
            arguments << e;

    return new DebugExpression("Block", arguments);
}

Expression *DebugExpressionManager::Call(Expression *f, Expression *self, int args) {
    std::list<DebugExpression *> arguments;

    arguments << f;
    arguments << self;
    arguments << literal(typenames[Variant::Integer], Utility::toString(args));

    return new DebugExpression("Call", arguments);
}

Expression *DebugExpressionManager::ClassDefinition(const std::string &name, Expression *superclass) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
    arguments << superclass;

    return new DebugExpression("ClassDefinition", arguments);
}

Expression *DebugExpressionManager::Constant(Object *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(value->getClass()->getName(), value->toString());

    return new DebugExpression("Constant", arguments);
}

Expression *DebugExpressionManager::ContextResolution(Expression *self, Expression *body, Expression *here) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << body;

    if (here)
        arguments << here;

    return new DebugExpression("ContextResolution", arguments);
}

Expression *DebugExpressionManager::Empty() {
    return new DebugExpression("Empty");
}

Expression *DebugExpressionManager::FunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) {
    std::list<DebugExpression *> arguments, parameters;

    arguments << literal(typenames[Variant::String], name);

    for (auto &param : params)
        parameters << literal(typenames[Variant::String], param);

    arguments << new DebugExpression("List", parameters);

    arguments << body;

    return new DebugExpression("FunctionDefinition", arguments);
}

Expression *DebugExpressionManager::Here() {
    return new DebugExpression("Here");
}

Expression *DebugExpressionManager::Identifier(const std::string &name) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);

    return new DebugExpression("Identifier", arguments);
}

Expression *DebugExpressionManager::If(Expression *condition, Expression *body, Expression *elseBody) {
    std::list<DebugExpression *> arguments;

    arguments << condition;
    arguments << body;

    if (elseBody)
        arguments << elseBody;

    return new DebugExpression("If", arguments);
}

Expression *DebugExpressionManager::Literal(const Variant &value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[value.getType()], value.toString());

    return new DebugExpression("Literal", arguments);
}

Expression *DebugExpressionManager::LocalAssignment(const std::string &name, Expression *value) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::String], name);
    arguments << value;

    return new DebugExpression("LocalAssignment", arguments);
}

Expression *DebugExpressionManager::Loop(Expression *condition, Expression *body) {
    std::list<DebugExpression *> arguments;

    arguments << condition;
    arguments << body;

    return new DebugExpression("Loop", arguments);
}

Expression *DebugExpressionManager::Not(Expression *self) {
    std::list<DebugExpression *> arguments;

    arguments << self;

    return new DebugExpression("Not", arguments);
}

Expression *DebugExpressionManager::Or(Expression *self, Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("Or", arguments);
}

Expression *DebugExpressionManager::Pop(int count) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::Integer], Utility::toString(count));

    return new DebugExpression("Pop", arguments);
}

Expression *DebugExpressionManager::Push(Expression *arg) {
    std::list<DebugExpression *> arguments;

    arguments << arg;

    return new DebugExpression("Push", arguments);
}

Expression *DebugExpressionManager::Self() {
    return new DebugExpression("Self");
}

Expression *DebugExpressionManager::Stack(int index) {
    std::list<DebugExpression *> arguments;

    arguments << literal(typenames[Variant::Integer], Utility::toString(index));

    return new DebugExpression("Stack", arguments);
}

DebugExpression *DebugExpressionManager::literal(const std::string &type, const std::string &value) {
    return new LiteralDebugExpression("<" + type + " : \"" + value + "\">");
}
}

#endif
