#include "expression/expressionmanager.h"

#include "expression/ast/andexpression.h"
#include "expression/ast/attributeassignmentexpression.h"
#include "expression/ast/attributeexpression.h"
#include "expression/ast/blockexpression.h"
#include "expression/ast/callexpression.h"
#include "expression/ast/classdefinitionexpression.h"
#include "expression/ast/constantexpression.h"
#include "expression/ast/contextresolutionexpression.h"
#include "expression/ast/emptyexpression.h"
#include "expression/ast/functiondefinitionexpression.h"
#include "expression/ast/hereexpression.h"
#include "expression/ast/identifierexpression.h"
#include "expression/ast/ifexpression.h"
#include "expression/ast/literalexpression.h"
#include "expression/ast/localassignmentexpression.h"
#include "expression/ast/assignmentexpression.h"
#include "expression/ast/loopexpression.h"
#include "expression/ast/notexpression.h"
#include "expression/ast/orexpression.h"
#include "expression/ast/popexpression.h"
#include "expression/ast/pushexpression.h"
#include "expression/ast/selfexpression.h"
#include "expression/ast/stackexpression.h"

namespace es {

Expression *ExpressionManager::And(Expression *self, Expression *arg) {
    return new AndExpression(self, arg);
}

Expression *ExpressionManager::Assignment(const std::string &name, Expression *value) {
    return new AssignmentExpression(name, value);
}

Expression *ExpressionManager::AttributeAssignment(Expression *self, const std::string &name, Expression *value) {
    return new AttributeAssignmentExpression(self, name, value);
}

Expression *ExpressionManager::Attribute(Expression *self, const std::string &name) {
    return new AttributeExpression(self, name);
}

Expression *ExpressionManager::Block(const std::list<Expression *> &nodes) {
    return new BlockExpression(nodes);
}

Expression *ExpressionManager::Call(Expression *f, Expression *self, int args) {
    return new CallExpression(f, self, args);
}

Expression *ExpressionManager::ClassDefinition(const std::string &name, Expression *superclass) {
    return new ClassDefinitionExpression(name, superclass);
}

Expression *ExpressionManager::Constant(Object *volatile value) {
    return new ConstantExpression(value);
}

Expression *ExpressionManager::ContextResolution(Expression *self, Expression *body, Expression *here) {
    return new ContextResolutionExpression(self, body, here);
}

Expression *ExpressionManager::Empty() {
    return new EmptyExpression;
}

Expression *ExpressionManager::FunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) {
    return new FunctionDefinitionExpression(name, params, body);
}

Expression *ExpressionManager::Here() {
    return new HereExpression;
}

Expression *ExpressionManager::Identifier(const std::string &name) {
    return new IdentifierExpression(name);
}

Expression *ExpressionManager::If(Expression *condition, Expression *body, Expression *elseBody) {
    return new IfExpression(condition, body, elseBody);
}

Expression *ExpressionManager::Literal(const Variant &value) {
    return new LiteralExpression(value);
}

Expression *ExpressionManager::LocalAssignment(const std::string &name, Expression *value) {
    return new LocalAssignmentExpression(name, value);
}

Expression *ExpressionManager::Loop(Expression *condition, Expression *body) {
    return new LoopExpression(condition, body);
}

Expression *ExpressionManager::Not(Expression *self) {
    return new NotExpression(self);
}

Expression *ExpressionManager::Or(Expression *self, Expression *arg) {
    return new OrExpression(self, arg);
}

Expression *ExpressionManager::Pop(int count) {
    return new PopExpression(count);
}

Expression *ExpressionManager::Push(Expression *arg) {
    return new PushExpression(arg);
}

Expression *ExpressionManager::Self() {
    return new SelfExpression;
}

Expression *ExpressionManager::Stack(int index) {
    return new StackExpression(index);
}
}
