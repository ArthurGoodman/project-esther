#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class DoExpression : public Expression {
    Expression *body, *condition;

public:
    DoExpression(Expression *body, Expression *condition);
    ~DoExpression();

    Object *eval(Context *context);
};
}
