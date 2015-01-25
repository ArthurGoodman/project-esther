#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class IdentifierExpression : public Expression {
    Expression *name;

public:
    IdentifierExpression(Expression *name);

    Object *eval(Context *context);
};
}
