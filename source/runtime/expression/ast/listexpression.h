#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class ListExpression : public Expression {
    list<Expression *> nodes;

public:
    ListExpression(list<Expression *> nodes);

    Object *eval(Context *context);
};
}
