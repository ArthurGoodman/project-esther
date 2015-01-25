#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class Object;

class LiteralExpression : public Expression {
    Object *value;

public:
    LiteralExpression(Object *value);

    Object *eval(Context *context);
};
}
