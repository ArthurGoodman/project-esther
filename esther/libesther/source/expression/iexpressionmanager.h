#pragma once

#include <list>
#include <string>

class Variant;
class Expression;
class Object;
class Context;

class IExpressionManager {
public:
    static IExpressionManager *instance();

    virtual ~IExpressionManager();

    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;
    virtual Expression *createAttributeAssignment(Expression *self, Expression *name, Expression *value) = 0;
    virtual Expression *createBlock(const std::list<Expression *> &nodes) = 0;
    virtual Expression *createCall(Expression *self, Expression *name, const std::list<Expression *> &args) = 0;
    virtual Expression *createConstant(Object *value) = 0;
    virtual Expression *createContextResolution(Expression *self, Expression *body, Context *context) = 0;
    virtual Expression *createDirectCall(Expression *self, const std::string &name, const std::list<Expression *> &args) = 0;
    virtual Expression *createDynamicCall(Expression *self, Expression *body, const std::list<Expression *> &args) = 0;
    virtual Expression *createEmpty() = 0;
    virtual Expression *createHere() = 0;
    virtual Expression *createIdentifier(Expression *name) = 0;
    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createLocalAssignment(Expression *name, Expression *value) = 0;
    virtual Expression *createLoop(Expression *condition, Expression *body) = 0;
    virtual Expression *createNot(Expression *self) = 0;
    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createSelf() = 0;
};
