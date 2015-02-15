#pragma once
#include "common.h"

#include "expression.h"

class ListExpression : public Expression {
    list<Expression *> nodes;

public:
    ListExpression(list<Expression *> nodes);

    Object *eval(Context *context);
};
