#pragma once

#include "expression.h"

class BlockExpression : public Expression {
    std::list<Expression *> nodes;

public:
    BlockExpression(const std::list<Expression *> &nodes);
    ~BlockExpression();

protected:
    Object *exec(Esther *esther);
};
