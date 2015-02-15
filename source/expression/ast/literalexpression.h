#pragma once
#include "common.h"

#include "expression.h"

class Object;

class LiteralExpression : public Expression {
    Object *value;

public:
    LiteralExpression(Object *value);

    Object *eval(Context *context);
};
