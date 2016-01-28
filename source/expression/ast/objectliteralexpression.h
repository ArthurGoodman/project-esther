#pragma once
#include "common.h"

#include "expression.h"

class ObjectLiteralExpression : public Expression {
    Expression *body;

public:
    ObjectLiteralExpression(Expression *body);

    IObject *exec(Context *context);
};
