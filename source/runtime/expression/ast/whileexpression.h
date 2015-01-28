#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class WhileExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    WhileExpression(Expression *condition, Expression *body, Expression *elseBody);
    ~WhileExpression();

    Object *eval(Context *context);
};
}
