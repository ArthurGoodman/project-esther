#include "expressionmanager.h"

#include "esther.h"
#include "emptyexpression.h"
#include "blockexpression.h"
#include "listexpression.h"
#include "tupleexpression.h"
#include "assignmentexpression.h"
#include "literalexpression.h"
#include "orexpression.h"
#include "andexpression.h"
#include "negateexpression.h"
#include "predecrementexpression.h"
#include "preincrementexpression.h"
#include "postdecrementexpression.h"
#include "postincrementexpression.h"
#include "identifierexpression.h"
#include "identifierdefinitionexpression.h"
#include "parameterexpression.h"
#include "callexpression.h"
#include "ifexpression.h"
#include "whileexpression.h"
#include "forexpression.h"
#include "doexpression.h"
#include "contextresolutionexpression.h"
#include "classexpression.h"
#include "functionexpression.h"
#include "methodexpression.h"
#include "returnexpression.h"
#include "breakexpression.h"
#include "continueexpression.h"
#include "selfexpression.h"
#include "hereexpression.h"
#include "staticexpression.h"
#include "includeexpression.h"
#include "objectliteralexpression.h"
#include "constantexpression.h"
#include "contextcallexpression.h"

Expression *ExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::createBlock(std::list<Expression *> nodes) {
    return new BlockExpression(nodes);
}

Expression *ExpressionManager::createList(std::list<Expression *> nodes) {
    return new ListExpression(nodes);
}

Expression *ExpressionManager::createTuple(std::list<Expression *> nodes) {
    return new TupleExpression(nodes);
}

Expression *ExpressionManager::createAssignment(Expression *tuple, Expression *value) {
    return new AssignmentExpression(tuple, value);
}

Expression *ExpressionManager::createLiteral(const Variant &value) {
    return new LiteralExpression(value);
}

Expression *ExpressionManager::createConstant(IObject *value) {
    return new ConstantExpression(value);
}

Expression *ExpressionManager::createOr(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *ExpressionManager::createAnd(Expression *self, Expression *arg) {
    return new AndExpression(self, arg);
}

Expression *ExpressionManager::createNegate(Expression *self) {
    return new NegateExpression(self);
}

Expression *ExpressionManager::createPreDecrement(Expression *self) {
    return new PreDecrementExpression(self);
}

Expression *ExpressionManager::createPreIncrement(Expression *self) {
    return new PreIncrementExpression(self);
}

Expression *ExpressionManager::createPostDecrement(Expression *self) {
    return new PostDecrementExpression(self);
}

Expression *ExpressionManager::createPostIncrement(Expression *self) {
    return new PostIncrementExpression(self);
}

Expression *ExpressionManager::createIdentifier(Expression *name, bool dynamic) {
    return new IdentifierExpression(name, dynamic);
}

Expression *ExpressionManager::createIdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) {
    return new IdentifierDefinitionExpression(type, name, value, dynamic);
}

Expression *ExpressionManager::createParameter(Expression *type, Expression *name, Expression *value, bool dynamic) {
    return new ParameterExpression(type, name, value, dynamic);
}

Expression *ExpressionManager::createCall(Expression *self, const std::string &name, std::list<Expression *> args) {
    return new CallExpression(self, name, args);
}

Expression *ExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    return new IfExpression(condition, body, elseBody);
}

Expression *ExpressionManager::createWhile(Expression *condition, Expression *body, Expression *elseBody) {
    return new WhileExpression(condition, body, elseBody);
}

Expression *ExpressionManager::createFor(Expression *param, Expression *expression, Expression *body) {
    return new ForExpression(param, expression, body);
}

Expression *ExpressionManager::createDo(Expression *body, Expression *condition) {
    return new DoExpression(body, condition);
}

Expression *ExpressionManager::createContextResolution(Expression *self, Expression *body) {
    return new ContextResolutionExpression(self, body);
}

Expression *ExpressionManager::createContextCall(Expression *self, Expression *body, std::list<Expression *> args) {
    return new ContextCallExpression(self, body, args);
}

Expression *ExpressionManager::createClassDefinition(Expression *name, Expression *superclass, Expression *body) {
    return new ClassExpression(name, superclass, body);
}

Expression *ExpressionManager::createFunctionDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
    return new FunctionExpression(type, name, params, body, variadic, dynamic);
}

Expression *ExpressionManager::createMethodDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) {
    return new MethodExpression(type, name, params, body, variadic, dynamic);
}

Expression *ExpressionManager::createReturn(Expression *value) {
    return new ReturnExpression(value);
}

Expression *ExpressionManager::createBreak(Expression *value) {
    return new BreakExpression(value);
}

Expression *ExpressionManager::createContinue() {
    return new ContinueExpression;
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}

Expression *ExpressionManager::createHere() {
    return new HereExpression;
}

Expression *ExpressionManager::createStatic(Expression *body) {
    return new StaticExpression(body);
}

Expression *ExpressionManager::createInclude(Expression *fileName) {
    return new IncludeExpression(fileName);
}

Expression *ExpressionManager::createObjectLiteral(Expression *body) {
    return new ObjectLiteralExpression(body);
}
