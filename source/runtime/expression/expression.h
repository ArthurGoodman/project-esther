#pragma once
#include <common.h>

#include "object.h"

namespace esther {

class ExpressionManager;
class Context;

class Expression : public Object {
    static ExpressionManager *manager;

public:
    static void initialize();
    static void release();

    static Expression *Empty();

    static Expression *Block(list<Expression *> nodes);
    static Expression *List(list<Expression *> nodes = list<Expression *>());

    static Expression *Literal(Object *value);

    static Expression *Or(Expression *self, Expression *arg);
    static Expression *And(Expression *self, Expression *arg);

    static Expression *Negate(Expression *self);

    static Expression *Identifier(Expression *name);
    static Expression *IdentifierAssignment(Expression *name, Expression *value);
    static Expression *LocalDefinition(Expression *type, Expression *name, Expression *value);

    static Expression *Call(Expression *self, string name, list<Expression *> args);
    static Expression *Call(Expression *self, string name, Expression *arg);
    static Expression *Call(Expression *self, string name);

    static Expression *CloneAndCall(Expression *self, string name);

    static Expression *If(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *While(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *For(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    static Expression *Do(Expression *body, Expression *condition);

    static Expression *ContextResolution(Expression *self, Expression *body);

    static Expression *Class(Expression *name, Expression *superclass, Expression *body);

    static Expression *Return(Expression *value);
    static Expression *Break(Expression *value);
    static Expression *Continue();

    virtual Object *eval(Context *context) = 0;
};
}
