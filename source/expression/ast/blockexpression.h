#pragma once
#include "common.h"

#include "expression.h"

class BlockExpression : public Expression {
    list<Expression *> nodes;

public:
    BlockExpression(list<Expression *> nodes);
    ~BlockExpression();

    Object *eval(Context *context);
};
