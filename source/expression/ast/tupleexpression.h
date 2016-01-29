#pragma once

#include "expression.h"

class TupleExpression : public Expression {
    std::list<Expression *> nodes;

public:
    TupleExpression(std::list<Expression *> nodes);

    std::list<Expression *> getNodes();

    IObject *exec(Context *context);
};
