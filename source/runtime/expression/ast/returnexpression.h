#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class ReturnExpression : public Expression {
    Expression *value;

public:
    ReturnExpression(Expression *value);

    Object *eval(Context *context);
};
}
