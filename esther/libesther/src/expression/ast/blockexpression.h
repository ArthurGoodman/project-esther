#pragma once

#include "expression/expression.h"

namespace es {

class BlockExpression : public Expression {
    std::list<Expression *> nodes;

public:
    BlockExpression(const std::list<Expression *> &nodes);
    ~BlockExpression();

protected:
    Object *exec(Esther *esther) override;
};
}
