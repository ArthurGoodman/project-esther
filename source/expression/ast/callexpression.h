#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class CallExpression : public Expression {
    Expression *self;
    string name;
    list<Expression *> args;

public:
    CallExpression(Expression *self, string name, list<Expression *> args);

    Object *eval(Context *context);
};
}
