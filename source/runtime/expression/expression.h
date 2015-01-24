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

    static Expression *Block(list<Expression *> nodes);
    static Expression *List(list<Expression *> nodes);

    static Expression *Literal(Object *value);

    static Expression *Call(Expression *self, string name, list<Expression *> args);
    static Expression *Call(Expression *self, string name, Expression *arg);

    static Expression *If(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *While(Expression *condition, Expression *body, Expression *elseBody);
    static Expression *For(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);
    static Expression *Do(Expression *body, Expression *condition);

    virtual Object *eval(Context *context) = 0;
};
}
