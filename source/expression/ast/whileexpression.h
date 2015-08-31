#pragma once
#include "common.h"

#include "expression.h"

class WhileExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    WhileExpression(Expression *condition, Expression *body, Expression *elseBody);

    Object *exec(Context *context);
};
