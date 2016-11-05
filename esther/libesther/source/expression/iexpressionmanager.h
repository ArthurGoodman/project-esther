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
    virtual Expression *createAttributeAssignment() = 0;
    virtual Expression *createBlock() = 0;
    virtual Expression *createConstant(Object *value) = 0;
    virtual Expression *createContextResolution() = 0;
    virtual Expression *createEmpty() = 0;
    virtual Expression *createHere() = 0;
    virtual Expression *createIdentifier() = 0;
    virtual Expression *createIf() = 0;
    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createLocalAssignment() = 0;
    virtual Expression *createLoop() = 0;
    virtual Expression *createNot() = 0;
    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createSelf() = 0;
};
