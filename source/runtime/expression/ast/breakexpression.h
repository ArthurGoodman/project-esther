#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class BreakExpression : public Expression {
    Expression *value;

public:
    BreakExpression(Expression *value);

    Object *eval(Context *context);
};
}
