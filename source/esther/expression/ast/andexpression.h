#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class AndExpression : public Expression {
    Expression *self, *arg;

public:
    AndExpression(Expression *self, Expression *arg);
    ~AndExpression();

    Object *eval(Context *context);
};
}
