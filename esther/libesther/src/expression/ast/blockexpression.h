#pragma once

#include "expression/expression.h"

class BlockExpression : public Expression {
    std::list<Expression *> nodes;

public:
    BlockExpression(const std::list<Expression *> &nodes);
    ~BlockExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
