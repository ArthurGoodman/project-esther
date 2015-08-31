#pragma once
#include "common.h"

#include "expression.h"

class CallExpression : public Expression {
    Expression *self;
    string name;
    list<Expression *> args;

public:
    CallExpression(Expression *self, string name, list<Expression *> args);

    Object *exec(Context *context);
};
