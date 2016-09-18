#pragma once

#include "expression.h"

class IdentifierExpression : public Expression {
    Expression *name;

public:
    IdentifierExpression(Expression *name);
    ~IdentifierExpression();

    Object *exec(Context *context);
};
