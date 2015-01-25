#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class LocalDefinitionExpression : public Expression {
    Expression *type, *name, *value;

public:
    LocalDefinitionExpression(Expression *type, Expression *name, Expression *value);

    Object *eval(Context *context);
};
}
