#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class EmptyExpression : public Expression {
public:
    Object *eval(Context *context);
};
}
