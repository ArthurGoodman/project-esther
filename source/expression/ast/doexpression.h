#pragma once
#include "common.h"

#include "expression.h"

class DoExpression : public Expression {
    Expression *body, *condition;

public:
    DoExpression(Expression *body, Expression *condition);

    Object *eval(Context *context);
};
