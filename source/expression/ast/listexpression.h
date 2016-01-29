#pragma once

#include "expression.h"

class ListExpression : public Expression {
    std::list<Expression *> nodes;

public:
    ListExpression(std::list<Expression *> nodes);

    IObject *exec(Context *context);
};
