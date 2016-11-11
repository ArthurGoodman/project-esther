#pragma once

#include "expression.h"

class CachedExpression : public Expression {
    Expression *body;
    Object *value;

public:
    CachedExpression(Expression *body);
    ~CachedExpression();

    Object *exec(Context *context);
};
