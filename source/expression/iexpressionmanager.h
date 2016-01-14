#pragma once
#include "common.h"

class Variant;
class Expression;
class Object;

class IExpressionManager {
public:
    static IExpressionManager *create();

    virtual ~IExpressionManager();

    virtual Expression *createEmpty() = 0;

    virtual Expression *createBlock(list<Expression *> nodes) = 0;
    virtual Expression *createList(list<Expression *> nodes) = 0;

    virtual Expression *createTuple(list<Expression *> nodes) = 0;

    virtual Expression *createLiteral(const Variant &value) = 0;
    virtual Expression *createConstant(Object *value) = 0;

    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;

    virtual Expression *createNegate(Expression *self) = 0;

    virtual Expression *createPreDecrement(Expression *self) = 0;
    virtual Expression *createPreIncrement(Expression *self) = 0;
    virtual Expression *createPostDecrement(Expression *self) = 0;
    virtual Expression *createPostIncrement(Expression *self) = 0;

    virtual Expression *createIdentifier(Expression *name, bool dynamic) = 0;
    virtual Expression *createIdentifierAssignment(Expression *name, Expression *value, bool dynamic) = 0;
    virtual Expression *createIdentifierDefinition(Expression *type, Expression *name, Expression *value, bool dynamic) = 0;

    virtual Expression *createParameter(Expression *type, Expression *name, Expression *value, bool dynamic) = 0;
    virtual Expression *createCall(Expression *self, string name, list<Expression *> args) = 0;

    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createFor(list<Expression *> params, Expression *expression, Expression *body) = 0;
    virtual Expression *createDo(Expression *body, Expression *condition) = 0;

    virtual Expression *createContextResolution(Expression *self, Expression *body) = 0;
    virtual Expression *createContextCall(Expression *self, Expression *body, list<Expression *> args) = 0;

    virtual Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body) = 0;

    virtual Expression *createFunctionDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic) = 0;
    virtual Expression *createMethodDefinition(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic) = 0;

    virtual Expression *createReturn(Expression *value) = 0;
    virtual Expression *createBreak(Expression *value) = 0;
    virtual Expression *createContinue() = 0;

    virtual Expression *createSelf() = 0;
    virtual Expression *createHere() = 0;

    virtual Expression *createStatic(Expression *body) = 0;
    virtual Expression *createInclude(Expression *fileName) = 0;
    virtual Expression *createObjectLiteral(Expression *body) = 0;
};
