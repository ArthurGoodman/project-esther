#pragma once

#include <list>
#include <string>

#include "object.h"

class Variant;
class Expression;
class Context;

class IExpressionManager {
public:
    static IExpressionManager *instance();

    virtual ~IExpressionManager();

    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;
    virtual Expression *createAssignment(const std::string &name, Expression *value) = 0;
    virtual Expression *createAttributeAssignment(Expression *self, const std::string &name, Expression *value) = 0;
    virtual Expression *createAttribute(Expression *self, const std::string &name) = 0;
    virtual Expression *createBlock(const std::list<Expression *> &nodes) = 0;
    virtual Expression *createCall(Expression *f, Expression *self, int args) = 0;
    virtual Expression *createClassDefinition(const std::string &name, Expression *superclass) = 0;
    virtual Expression *createConstant(Ptr<Object> value) = 0;
    virtual Expression *createContextResolution(Expression *self, Expression *body, Expression *here) = 0;
    virtual Expression *createEmpty() = 0;
    virtual Expression *createFunctionDefinition(const std::string &name, const std::list<std::string> &params, Expression *body) = 0;
    virtual Expression *createHere() = 0;
    virtual Expression *createIdentifier(const std::string &name) = 0;
    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createLocalAssignment(const std::string &name, Expression *value) = 0;
    virtual Expression *createLoop(Expression *condition, Expression *body) = 0;
    virtual Expression *createNot(Expression *self) = 0;
    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createPop(int count) = 0;
    virtual Expression *createPush(Expression *arg) = 0;
    virtual Expression *createSelf() = 0;
    virtual Expression *createStack(int index) = 0;
};
