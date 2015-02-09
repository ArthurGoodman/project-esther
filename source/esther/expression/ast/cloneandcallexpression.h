#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class CloneAndCallExpression : public Expression {
    Expression *self;
    string name;

public:
    CloneAndCallExpression(Expression *self, string name);

    Object *eval(Context *context);
};
}
