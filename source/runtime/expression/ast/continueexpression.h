#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class ContinueExpression : public Expression {
public:
    Object *eval(Context *context);
};
}
