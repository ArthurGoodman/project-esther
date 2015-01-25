#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class ContextResolutionExpression : public Expression {
    Expression *self, *body;

public:
    ContextResolutionExpression(Expression *self, Expression *body);

    Object *eval(Context *context);
};
}
