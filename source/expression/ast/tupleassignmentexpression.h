#pragma once

#include "expression.h"

class TupleAssignmentExpression : public Expression {
    Expression *tuple, *value;

public:
    TupleAssignmentExpression(Expression *tuple, Expression *value);

    Object *exec(Context *context);
};
