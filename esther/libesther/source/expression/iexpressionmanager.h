#pragma once

#include <list>
#include <string>

class Variant;
class Expression;
class Object;

template <class>
class Pointer;

class IExpressionManager {
public:
    static IExpressionManager *instance();

    virtual ~IExpressionManager();

    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;
    virtual Expression *createAttributeAssignment(Expression *name, Expression *value) = 0;
    virtual Expression *createBlock(const std::list<Expression *> &nodes) = 0;
    virtual Expression *createCall() = 0;
    virtual Expression *createConstant(Object *value) = 0;
    virtual Expression *createContextCall() = 0;
    virtual Expression *createContextResolution() = 0;
    virtual Expression *createEmpty() = 0;
    virtual Expression *createHere() = 0;
    virtual Expression *createIdentifier() = 0;
    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createLocalAssignment(Expression *name, Expression *value) = 0;
    virtual Expression *createLoop() = 0;
    virtual Expression *createNot(Expression *self) = 0;
    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createSelf() = 0;
};
