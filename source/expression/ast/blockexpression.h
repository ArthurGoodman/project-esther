#pragma once

#include "expression.h"

class BlockExpression : public Expression {
    std::list<Expression *> nodes;

public:
    BlockExpression(std::list<Expression *> nodes);

    IObject *exec(Context *context);
};
