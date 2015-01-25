#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class BlockExpression : public Expression {
    list<Expression *> nodes;

public:
    BlockExpression(list<Expression *> nodes);

    Object *eval(Context *context);
};
}
