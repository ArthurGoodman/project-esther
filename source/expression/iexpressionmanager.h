#pragma once

#include <list>
#include <string>

class Variant;
class Expression;
class IObject;

class IExpressionManager {
public:
    static IExpressionManager *instance();

    virtual ~IExpressionManager();

    virtual Expression *createEmpty() = 0;

    virtual Expression *createBlock(std::list<Expression *> nodes) = 0;
    virtual Expression *createList(std::list<Expression *> nodes) = 0;

    virtual Expression *createTuple(std::list<Expression *> nodes) = 0;
    virtual Expression *createAssignment(Expression *expression, Expression *value) = 0;

    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createConstant(IObject *value) = 0;

    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;

    virtual Expression *createNegate(Expression *self) = 0;

    virtual Expression *createPreDecrement(Expression *self) = 0;
    virtual Expression *createPreIncrement(Expression *self) = 0;
    virtual Expression *createPostDecrement(Expression *self) = 0;
    virtual Expression *createPostIncrement(Expression *self) = 0;

    virtual Expression *createIdentifier(Expression *name, bool dynamic) = 0;
    virtual Expression *createIdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) = 0;

    virtual Expression *createParameter(Expression *type, Expression *name, Expression *value, bool dynamic) = 0;
    virtual Expression *createCall(Expression *self, const std::string &name, std::list<Expression *> args) = 0;

    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createFor(Expression * param, Expression *expression, Expression *body) = 0;
    virtual Expression *createDo(Expression *body, Expression *condition) = 0;

    virtual Expression *createContextResolution(Expression *self, Expression *body) = 0;
    virtual Expression *createContextCall(Expression *self, Expression *body, std::list<Expression *> args) = 0;

    virtual Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body) = 0;

    virtual Expression *createFunctionDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) = 0;
    virtual Expression *createMethodDefinition(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic) = 0;

    virtual Expression *createReturn(Expression *value) = 0;
    virtual Expression *createBreak(Expression *value) = 0;
    virtual Expression *createContinue() = 0;

    virtual Expression *createSelf() = 0;
    virtual Expression *createHere() = 0;

    virtual Expression *createStatic(Expression *body) = 0;
    virtual Expression *createInclude(Expression *fileName) = 0;
    virtual Expression *createObjectLiteral(Expression *body) = 0;
};
