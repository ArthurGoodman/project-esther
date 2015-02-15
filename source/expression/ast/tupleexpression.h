#pragma once
#include "common.h"

#include "expression.h"

class TupleExpression : public Expression {
    list<Expression *> nodes;

public:
    TupleExpression(list<Expression *> nodes);

    Object *eval(Context *context);
};
