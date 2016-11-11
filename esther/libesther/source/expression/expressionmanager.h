#pragma once

#include "iexpressionmanager.h"

class ExpressionManager : public IExpressionManager {
public:
    Expression *createAnd(Expression *self, Expression *arg);
    Expression *createAttributeAssignment(Expression *self, const std::string &name, Expression *value);
    Expression *createBlock(const std::list<Expression *> &nodes);
    Expression *createCached(Expression *body);
    Expression *createCall(const std::string &name, const std::list<Expression *> &args);
    Expression *createConstant(Object *value);
    Expression *createContextResolution(Expression *self, Expression *body, Context *context);
    Expression *createDirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args);
    Expression *createDynamicCall(Expression *body, const std::list<Expression *> &args);
    Expression *createEmpty();
    Expression *createHere();
    Expression *createIdentifier(const std::string &name);
    Expression *createIf(Expression *condition, Expression *body, Expression *elseBody);
    Expression *createLiteral(const Variant &value);
    Expression *createLocalAssignment(const std::string &name, Expression *value);
    Expression *createLoop(Expression *condition, Expression *body);
    Expression *createNativeCall(Object *(*f)(Context *...), const std::list<Expression *> &args);
    Expression *createNot(Expression *self);
    Expression *createOr(Expression *self, Expression *arg);
    Expression *createSelf();
};
