#include "expressionmanager.h"

#include "andexpression.h"
#include "attributeassignmentexpression.h"
#include "attributeexpression.h"
#include "blockexpression.h"
#include "callexpression.h"
#include "classdefinitionexpression.h"
#include "constantexpression.h"
#include "contextresolutionexpression.h"
#include "emptyexpression.h"
#include "functiondefinitionexpression.h"
#include "hereexpression.h"
#include "identifierexpression.h"
#include "ifexpression.h"
#include "literalexpression.h"
#include "localassignmentexpression.h"
#include "assignmentexpression.h"
#include "loopexpression.h"
#include "notexpression.h"
#include "orexpression.h"
#include "popexpression.h"
#include "pushexpression.h"
#include "selfexpression.h"
#include "stackexpression.h"

Expression *ExpressionManager::createAnd(Expression *self, Expression *arg) {
    return new AndExpression(self, arg);
}

Expression *ExpressionManager::createAssignment(const std::string &name, Expression *value) {
    return new AssignmentExpression(name, value);
}

Expression *ExpressionManager::createAttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    return new AttributeAssignmentExpression(self, name, value);
}

Expression *ExpressionManager::createAttribute(Expression *self, const std::string &name) {
    return new AttributeExpression(self, name);
}

Expression *ExpressionManager::createBlock(const std::list<Expression *> &nodes) {
    return new BlockExpression(nodes);
}

Expression *ExpressionManager::createCall(Expression *f, Expression *self, int args) {
    return new CallExpression(f, self, args);
}

Expression *ExpressionManager::createClassDefinition(const std::string &name, Expression *superclass) {
    return new ClassDefinitionExpression(name, superclass);
}

Expression *ExpressionManager::createConstant(Pointer<Object> value) {
    return new ConstantExpression(value);
}

Expression *ExpressionManager::createContextResolution(Expression *self, Expression *body, Expression *here) {
    return new ContextResolutionExpression(self, body, here);
}

Expression *ExpressionManager::createEmpty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) {
    return new FunctionDefinitionExpression(name, params, body);
}

Expression *ExpressionManager::createHere() {
    return new HereExpression;
}

Expression *ExpressionManager::createIdentifier(const std::string &name) {
    return new IdentifierExpression(name);
}

Expression *ExpressionManager::createIf(Expression *condition, Expression *body, Expression *elseBody) {
    return new IfExpression(condition, body, elseBody);
}

Expression *ExpressionManager::createLiteral(const Variant &value) {
    return new LiteralExpression(value);
}

Expression *ExpressionManager::createLocalAssignment(const std::string &name, Expression *value) {
    return new LocalAssignmentExpression(name, value);
}

Expression *ExpressionManager::createLoop(Expression *condition, Expression *body) {
    return new LoopExpression(condition, body);
}

Expression *ExpressionManager::createNot(Expression *self) {
    return new NotExpression(self);
}

Expression *ExpressionManager::createOr(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *ExpressionManager::createPop(int count) {
    return new PopExpression(count);
}

Expression *ExpressionManager::createPush(Expression *arg) {
    return new PushExpression(arg);
}

Expression *ExpressionManager::createSelf() {
    return new SelfExpression;
}

Expression *ExpressionManager::createStack(int index) {
    return new StackExpression(index);
}
