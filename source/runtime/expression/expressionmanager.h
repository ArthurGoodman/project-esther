#pragma once
#include <common.h>

namespace esther {

class Expression;
class Object;

class ExpressionManager {
public:
    static ExpressionManager *create();

    virtual ~ExpressionManager();

    virtual Expression *createBlock(list<Expression *> nodes) = 0;
    virtual Expression *createList(list<Expression *> nodes) = 0;

    virtual Expression *createLiteral(Object *value) = 0;

    virtual Expression *createIdentifier(Expression *name) = 0;
    virtual Expression *createIdentifierAssignment(Expression *name, Expression *value) = 0;
    virtual Expression *createLocalDefinition(Expression *type, Expression *name, Expression *value) = 0;

    virtual Expression *createCall(Expression *self, string name, list<Expression *> args) = 0;

    virtual Expression *createCloneAndCall(Expression *self, string name) = 0;

    virtual Expression *createIf(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createWhile(Expression *condition, Expression *body, Expression *elseBody) = 0;
    virtual Expression *createFor(Expression *preffix, Expression *condition, Expression *suffix, Expression *body) = 0;
    virtual Expression *createDo(Expression *body, Expression *condition) = 0;

    virtual Expression *createContextResolution(Expression *self, Expression *body) = 0;
};
}
