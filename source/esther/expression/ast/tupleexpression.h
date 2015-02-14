#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class TupleExpression : public Expression {
    list<Expression *> nodes;

public:
    TupleExpression(list<Expression *> nodes);
    ~TupleExpression();

    Object *eval(Context *context);
};
}
