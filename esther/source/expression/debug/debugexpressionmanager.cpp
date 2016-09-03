#include "debugexpressionmanager.h"

#include "common.h"
#include "debugexpression.h"
//#include "valueobject.h"
#include "class.h"
#include "runtime.h"
//#include "stringvalueobject.h"

#if DEBUG_PARSER

Expression *DebugExpressionManager::createEmpty() {
    return new DebugExpression("Empty");
}

//Expression *DebugExpressionManager::createBlock(std::list<Expression *> nodes) {
//    std::list<Object *> arguments;

//    for (Expression *e : nodes)
//        arguments << e;

//    return new DebugExpression("Block", arguments);
//}

//Expression *DebugExpressionManager::createList(std::list<Expression *> nodes) {
//    std::list<Object *> arguments;

//    for (Expression *e : nodes)
//        arguments << e;

//    return new DebugExpression("List", arguments);
//}

//Expression *DebugExpressionManager::createTuple(std::list<Expression *> nodes) {
//    std::list<Object *> arguments;

//    for (Expression *e : nodes)
//        arguments << e;

//    return new DebugExpression("Tuple", arguments);
//}

//Expression *DebugExpressionManager::createAssignment(Expression *expresion, Expression *value) {
//    std::list<Object *> arguments;

//    arguments << expresion;
//    arguments << value;

//    return new DebugExpression("Assignment", arguments);
//}

//Expression *DebugExpressionManager::createLiteral(const Variant &value) {
//    std::list<Object *> arguments;

//    Object *object = ValueObject::createNewInstance(value);
//    arguments << new String("<" + object->getClass()->getName() + " : \"" + object->toString() + "\">");

//    return new DebugExpression("Literal", arguments);
//}

//Expression *DebugExpressionManager::createConstant(Object *value) {
//    std::list<Object *> arguments;

//    arguments << new String("<" + value->getClass()->getName() + " : \"" + value->toString() + "\">");

//    return new DebugExpression("Constant", arguments);
//}

//Expression *DebugExpressionManager::createOr(Expression *self, Expression *arg) {
//    std::list<Object *> arguments;

//    arguments << self;
//    arguments << arg;

//    return new DebugExpression("Or", arguments);
//}

//Expression *DebugExpressionManager::createAnd(Expression *self, Expression *arg) {
//    std::list<Object *> arguments;

//    arguments << self;
//    arguments << arg;

//    return new DebugExpression("And", arguments);
//}

//Expression *DebugExpressionManager::createNegate(Expression *self) {
//    std::list<Object *> arguments;

//    arguments << self;

//    return new DebugExpression("Negate", arguments);
//}

//Expression *DebugExpressionManager::createPreDecrement(Expression *self) {
//    std::list<Object *> arguments;

//    arguments << self;

//    return new DebugExpression("PreDecrement", arguments);
//}

//Expression *DebugExpressionManager::createPreIncrement(Expression *self) {
//    std::list<Object *> arguments;

//    arguments << self;

//    return new DebugExpression("PreIncrement", arguments);
//}

//Expression *DebugExpressionManager::createPostDecrement(Expression *self) {
//    std::list<Object *> arguments;

//    arguments << self;

//    return new DebugExpression("PostDecrement", arguments);
//}

//Expression *DebugExpressionManager::createPostIncrement(Expression *self) {
//    std::list<Object *> arguments;

//    arguments << self;

//    return new DebugExpression("PostIncrement", arguments);
//}

//Expression *DebugExpressionManager::createIdentifier(Expression *name, bool dynamic) {
//    std::list<Object *> arguments;

//    arguments << name;

//    arguments << new DebugExpression("Dynamic", {Runtime::toBoolean(dynamic)});

//    return new DebugExpression("Identifier", arguments);
//}

//Expression *DebugExpressionManager::createIdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) {
//    std::list<Object *> arguments;

//    if (type)
//        arguments << type;

//    arguments << name;

//    if (value)
//        arguments << value;

//    arguments << new DebugExpression("Dynamic", {Runtime::toBoolean(dynamic)});

//    return new DebugExpression("IdentifierDefinition", arguments);
//}

//Expression *DebugExpressionManager::createParameter(Expression *type, Expression *name, Expression *value, bool dynamic) {
//    std::list<Object *> arguments;

//    if (type)
//        arguments << type;

//    arguments << name;

//    if (value)
//        arguments << value;

//    arguments << new DebugExpression("Dynamic", {Runtime::toBoolean(dynamic)});

//    return new DebugExpression("Parameter", arguments);
//}

//Expression *DebugExpressionManager::createCall(Expression *self, const std::string &name, std::list<Expression *> args) {
//    std::list<Object *> arguments, callArguments;

//    arguments << self;
//    arguments << new String("<String : \"" + name + "\">");

//    for (Expression *arg : args)
//        callArguments << arg;

//    arguments << new DebugExpression("List", callArguments);

//    return new DebugExpression("Call", arguments);
//}

//Expression *DebugExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
//    std::list<Object *> arguments;

//    arguments << condition;
//    arguments << body;

//    if (elseBody)
//        arguments << elseBody;

//    return new DebugExpression("If", arguments);
//}

//Expression *DebugExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
//    std::list<Object *> arguments;

//    arguments << condition;
//    arguments << body;

//    if (elseBody)
//        arguments << elseBody;

//    return new DebugExpression("While", arguments);
//}

//Expression *DebugExpressionManager::createFor(Expression *param, Expression *expression, Expression *body) {
//    std::list<Object *> arguments;

//    arguments << param;
//    arguments << expression;
//    arguments << body;

//    return new DebugExpression("For", arguments);
//}

//Expression *DebugExpressionManager::createDo(Expression *body, Expression *condition) {
//    std::list<Object *> arguments;

//    arguments << body;
//    arguments << condition;

//    return new DebugExpression("Do", arguments);
//}

//Expression *DebugExpressionManager::createContextResolution(Expression *self, Expression *body) {
//    std::list<Object *> arguments;

//    arguments << self;
//    arguments << body;

//    return new DebugExpression("ContextResolution", arguments);
//}

//Expression *DebugExpressionManager::createContextCall(Expression *self, Expression *body, std::list<Expression *> args) {
//    std::list<Object *> arguments, callArguments;

//    arguments << self;
//    arguments << body;

//    for (Expression *arg : args)
//        callArguments << arg;

//    arguments << new DebugExpression("List", callArguments);

//    return new DebugExpression("ContextCall", arguments);
//}

//Expression *DebugExpressionManager::createClassDefinition(Expression *name, Expression *superclass, Expression *body) {
//    std::list<Object *> arguments;

//    if (name)
//        arguments << name;

//    if (superclass)
//        arguments << superclass;

//    arguments << body;

//    return new DebugExpression("Class", arguments);
//}

//Expression *DebugExpressionManager::createFunctionDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
//    std::list<Object *> arguments, paramsArguments;

//    if (type)
//        arguments << type;

//    if (name)
//        arguments << name;

//    for (Expression *param : params)
//        paramsArguments << param;

//    arguments << new DebugExpression("List", paramsArguments);

//    arguments << body;

//    arguments << new DebugExpression("Variadic", {Runtime::toBoolean(variadic)});

//    arguments << new DebugExpression("Dynamic", {Runtime::toBoolean(dynamic)});

//    return new DebugExpression("Function", arguments);
//}

//Expression *DebugExpressionManager::createMethodDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
//    std::list<Object *> arguments, paramsArguments;

//    if (type)
//        arguments << type;

//    if (name)
//        arguments << name;

//    for (Expression *param : params)
//        paramsArguments << param;

//    arguments << new DebugExpression("List", paramsArguments);

//    arguments << body;

//    arguments << new DebugExpression("Variadic", {Runtime::toBoolean(variadic)});

//    arguments << new DebugExpression("Dynamic", {Runtime::toBoolean(dynamic)});

//    return new DebugExpression("Method", arguments);
//}

//Expression *DebugExpressionManager::createReturn(Expression *value) {
//    std::list<Object *> arguments;

//    if (value)
//        arguments << value;

//    return new DebugExpression("Return", arguments);
//}

//Expression *DebugExpressionManager::createBreak(Expression *value) {
//    std::list<Object *> arguments;

//    if (value)
//        arguments << value;

//    return new DebugExpression("Break", arguments);
//}

//Expression *DebugExpressionManager::createContinue() {
//    return new DebugExpression("Continue");
//}

//Expression *DebugExpressionManager::createSelf() {
//    return new DebugExpression("Self");
//}

//Expression *DebugExpressionManager::createHere() {
//    return new DebugExpression("Here");
//}

//Expression *DebugExpressionManager::createStatic(Expression *body) {
//    std::list<Object *> arguments;

//    arguments << body;

//    return new DebugExpression("Static", arguments);
//}

//Expression *DebugExpressionManager::createInclude(Expression *fileName) {
//    std::list<Object *> arguments;

//    arguments << fileName;

//    return new DebugExpression("Include", arguments);
//}

//Expression *DebugExpressionManager::createObjectLiteral(Expression *body) {
//    std::list<Object *> arguments;

//    arguments << body;

//    return new DebugExpression("ObjectLiteral", arguments);
//}

#endif
