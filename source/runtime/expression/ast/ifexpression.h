#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class IfExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    IfExpression(Expression *condition, Expression *body, Expression *elseBody);

    Object *eval(Context *context);
};
}
