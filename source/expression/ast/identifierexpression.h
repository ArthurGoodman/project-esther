#pragma once
#include "common.h"

#include "expression.h"

class IdentifierExpression : public Expression {
protected:
    Expression *name;

public:
    IdentifierExpression(Expression *name);

    Object *exec(Context *context);
};
