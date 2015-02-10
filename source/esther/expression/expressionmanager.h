#pragma once
#include "common.h"

namespace esther {

class Expression;
class Object;

class ExpressionManager {
public:
    static ExpressionManager *create();

    virtual ~ExpressionManager();

    virtual Expression *createEmpty() = 0;

    virtual Expression *createBlock(list<Expression *> nodes) = 0;
    virtual Expression *createList(list<Expression *> nodes) = 0;

    virtual Expression *createLiteral(Object *value) = 0;

    virtual Expression *createOr(Expression *self, Expression *arg) = 0;
    virtual Expression *createAnd(Expression *self, Expression *arg) = 0;

    virtual Expression *createNegate(Expression *self) = 0;

    virtual Expression *createPreDecrement(Expression *self) = 0;
    virtual Expression *createPreIncrement(Expression *self) = 0;
    virtual Expression *createPostDecrement(Expression *self) = 0;
    virtual Expression *createPostIncrement(Expression *self) = 0;

    virtual Expression *createIdentifier(Expression *name) = 0;
    virtual Expression *createIdentifierAssignment(Expression *name, Expression *value) = 0;
    virtual Expression *createIdentifierDefinition(Expression *name, Expression *value) = 0;

    virtual Expression *createCall(Expression *self, string name, list<Expression *> args) = 0;

    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) = 0;
    virtual Expression *createDo(Expression *body, Expression *condition) = 0;

    virtual Expression *createContextResolution(Expression *self, Expression *body) = 0;

    virtual Expression *createClassDefinition(Expression *name, Expression *superclass, Expression *body) = 0;

    virtual Expression *createReturn(Expression *value) = 0;
    virtual Expression *createBreak(Expression *value) = 0;
    virtual Expression *createContinue() = 0;
};
}
