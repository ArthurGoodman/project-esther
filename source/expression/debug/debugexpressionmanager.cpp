#include "debugexpressionmanager.h"

#include "debugexpression.h"
#include "valueobject.h"
#include "class.h"

#if DEBUG_PARSER

Expression *DebugExpressionManager::createEmpty() {
    return new DebugExpression("Empty");
}

Expression *DebugExpressionManager::createBlock(list<Expression *> nodes) {
    list<Object *> arguments;

    foreach (i, nodes)
        arguments << *i;

    return new DebugExpression("Block", arguments);
}

Expression *DebugExpressionManager::createList(list<Expression *> nodes) {
    list<Object *> arguments;

    foreach (i, nodes)
        arguments << *i;

    return new DebugExpression("List", arguments);
}

Expression *DebugExpressionManager::createTuple(list<Expression *> nodes) {
    list<Object *> arguments;

    foreach (i, nodes)
        arguments << *i;

    return new DebugExpression("Tuple", arguments);
}

Expression *DebugExpressionManager::createLiteral(Object *value) {
    list<Object *> arguments;

    arguments << new ValueObject("<" + value->getClass()->getName() + " : \"" + value->toString() + "\">");

    return new DebugExpression("Literal", arguments);
}

Expression *DebugExpressionManager::createOr(Expression *self, Expression *arg) {
    list<Object *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("Or", arguments);
}

Expression *DebugExpressionManager::createAnd(Expression *self, Expression *arg) {
    list<Object *> arguments;

    arguments << self;
    arguments << arg;

    return new DebugExpression("And", arguments);
}

Expression *DebugExpressionManager::createNegate(Expression *self) {
    list<Object *> arguments;

    arguments << self;

    return new DebugExpression("Negate", arguments);
}

Expression *DebugExpressionManager::createPreDecrement(Expression *self) {
    list<Object *> arguments;

    arguments << self;

    return new DebugExpression("PreDecrement", arguments);
}

Expression *DebugExpressionManager::createPreIncrement(Expression *self) {
    list<Object *> arguments;

    arguments << self;

    return new DebugExpression("PreIncrement", arguments);
}

Expression *DebugExpressionManager::createPostDecrement(Expression *self) {
    list<Object *> arguments;

    arguments << self;

    return new DebugExpression("PostDecrement", arguments);
}

Expression *DebugExpressionManager::createPostIncrement(Expression *self) {
    list<Object *> arguments;

    arguments << self;

    return new DebugExpression("PostIncrement", arguments);
}

Expression *DebugExpressionManager::createIdentifier(Expression *name) {
    list<Object *> arguments;

    arguments << name;

    return new DebugExpression("Identifier", arguments);
}

Expression *DebugExpressionManager::createIdentifierAssignment(Expression *name, Expression *value) {
    list<Object *> arguments;

    arguments << name;
    arguments << value;

    return new DebugExpression("IdentifierAssignment", arguments);
}

Expression *DebugExpressionManager::createIdentifierDefinition(Expression *type, Expression *name, Expression *value) {
    list<Object *> arguments;

    if (type)
        arguments << type;

    arguments << name;

    if (value)
        arguments << value;

    return new DebugExpression("IdentifierDefinition", arguments);
}

Expression *DebugExpressionManager::createParameter(Expression *type, Expression *name, Expression *value) {
    list<Object *> arguments;

    if (type)
        arguments << type;

    arguments << name;

    if (value)
        arguments << value;

    return new DebugExpression("Parameter", arguments);
}

Expression *DebugExpressionManager::createCall(Expression *self, string name, list<Expression *> args) {
    list<Object *> arguments, callArguments;

    arguments << self;
    arguments << new ValueObject("<String : \"" + name + "\">");

    foreach (i, args)
        callArguments << *i;

    arguments << new DebugExpression("List", callArguments);

    return new DebugExpression("Call", arguments);
}

Expression *DebugExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    list<Object *> arguments;

    arguments << condition;
    arguments << body;

    if (elseBody)
        arguments << elseBody;

    return new DebugExpression("If", arguments);
}

Expression *DebugExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
    list<Object *> arguments;

    arguments << condition;
    arguments << body;

    if (elseBody)
        arguments << elseBody;

    return new DebugExpression("While", arguments);
}

Expression *DebugExpressionManager::createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) {
    list<Object *> arguments;

    arguments << preffix;
    arguments << condition;
    arguments << suffix;
    arguments << body;

    return new DebugExpression("For", arguments);
}

Expression *DebugExpressionManager::createDo(Expression *body, Expression *condition) {
    list<Object *> arguments;

    arguments << body;
    arguments << condition;

    return new DebugExpression("Do", arguments);
}

Expression *DebugExpressionManager::createContextResolution(Expression *self, Expression *body) {
    list<Object *> arguments;

    arguments << self;
    arguments << body;

    return new DebugExpression("ContextResolution", arguments);
}

Expression *DebugExpressionManager::createClassDefinition(Expression *name, Expression *superclass, Expression *body) {
    list<Object *> arguments;

    if (name)
        arguments << name;

    if (superclass)
        arguments << superclass;

    arguments << body;

    return new DebugExpression("Class", arguments);
}

Expression *DebugExpressionManager::createFunctionDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body) {
    list<Object *> arguments, paramsArguments;

    if (type)
        arguments << type;

    if (name)
        arguments << name;

    foreach (i, params)
        paramsArguments << *i;

    arguments << new DebugExpression("List", paramsArguments);

    arguments << body;

    return new DebugExpression("Function", arguments);
}

Expression *DebugExpressionManager::createMethodDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body) {
    list<Object *> arguments, paramsArguments;

    if (type)
        arguments << type;

    if (name)
        arguments << name;

    foreach (i, params)
        paramsArguments << *i;

    arguments << new DebugExpression("List", paramsArguments);

    arguments << body;

    return new DebugExpression("Method", arguments);
}

Expression *DebugExpressionManager::createReturn(Expression *value) {
    list<Object *> arguments;

    if (value)
        arguments << value;

    return new DebugExpression("Return", arguments);
}

Expression *DebugExpressionManager::createBreak(Expression *value) {
    list<Object *> arguments;

    if (value)
        arguments << value;

    return new DebugExpression("Break", arguments);
}

Expression *DebugExpressionManager::createContinue() {
    return new DebugExpression("Continue");
}

Expression *DebugExpressionManager::createSelf() {
    return new DebugExpression("Self");
}

Expression *DebugExpressionManager::createHere() {
    return new DebugExpression("Here");
}

#endif
