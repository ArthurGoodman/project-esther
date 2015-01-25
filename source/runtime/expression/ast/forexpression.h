#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class ForExpression : public Expression {
    Expression *preffix, *condition, *suffix, *body;

public:
    ForExpression(Expression *preffix, Expression *condition, Expression *suffix, Expression *body);

    Object *eval(Context *context);
};
}
