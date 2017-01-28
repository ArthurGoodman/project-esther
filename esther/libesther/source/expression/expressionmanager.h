#pragma once

#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd(Expression *self, Expression *arg);
    Expression *createAssignment(const std::string &name, Expression *value);
    Expression *createAttributeAssignment(Expression *self, const std::string &name, Expression *value);
    Expression *createAttribute(Expression *self, const std::string &name);
    Expression *createBlock(const std::list<Expression *> &nodes);
    Expression *createCall(const std::string &name, const std::list<Expression *> &args);
    Expression *createClassDefinition(const std::string &name, Expression *superclass, Expression *body);
    Expression *createConstant(Object *value);
    Expression *createContextResolution(Expression *self, Expression *here, Expression *body);
    Expression *createContextCall(Expression *self, Expression *body, const std::list<Expression *> &args);
    Expression *createDirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args);
    Expression *createDynamicCall(Expression *body, const std::list<Expression *> &args);
    Expression *createEmpty();
    Expression *createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body);
    Expression *createHere();
    Expression *createIdentifier(const std::string &name);
    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createLiteral(const Variant &value);
    Expression *createLocalAssignment(const std::string &name, Expression *value);
    Expression *createLoop(Expression *condition, Expression *body);
    Expression *createNot(Expression *self);
    Expression *createOr(Expression *self, Expression *arg);
    Expression *createSelf();
};
