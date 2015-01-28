#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class OrExpression : public Expression {
    Expression *self, *arg;

public:
    OrExpression(Expression *self, Expression *arg);
    ~OrExpression();

    Object *eval(Context *context);
};
}
