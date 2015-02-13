#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class SelfExpression : public Expression {
public:
    Object *eval(Context *context);
};
}
