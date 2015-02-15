#pragma once
#include "common.h"

#include "object.h"

class ExpressionManager;
class Context;

class Expression : public Object {
    static ExpressionManager *manager;

public:
    static void initialize();
    static void release();

    static Expression *Empty();

    static Expression *Block(list<Expression *> nodes);
    static Expression *List(list<Expression *> nodes);

    static Expression *TupleLiteral(list<Expression *> nodes = list<Expression *>());

    static Expression *Literal(Object *value);

    static Expression *Or(Expression *self, Expression *arg);
    static Expression *And(Expression *self, Expression *arg);

    static Expression *Negate(Expression *self);

    static Expression *PreDecrement(Expression *self);
    static Expression *PreIncrement(Expression *self);
    static Expression *PostDecrement(Expression *self);
    static Expression *PostIncrement(Expression *self);

    static Expression *Identifier(Expression *name);
    static Expression *IdentifierAssignment(Expression *name, Expression *value);
    static Expression *IdentifierDefinition(Expression *type, Expression *name, Expression *value);

    static Expression *Call(Expression *self, string name, list<Expression *> args);
    static Expression *Call(Expression *self, string name, Expression *arg);
    static Expression *Call(Expression *self, string name);

    static Expression *If(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *While(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *For(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    static Expression *Do(Expression *body, Expression *condition);

    static Expression *ContextResolution(Expression *self, Expression *body);

    static Expression *ClassDefinition(Expression *name, Expression *superclass, Expression *body);

    static Expression *Return(Expression *value);
    static Expression *Break(Expression *value);
    static Expression *Continue();

    static Expression *Self();

    virtual Object *eval(Context *context) = 0;
};
