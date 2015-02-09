#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class IdentifierExpression : public Expression {
protected:
    Expression *name;

public:
    IdentifierExpression(Expression *name);
    ~IdentifierExpression();

    Object *eval(Context *context);
};
}
