#pragma once
#include "common.h"

#include "expression.h"

class IdentifierExpression : public Expression {
protected:
    Expression *name;
    bool dynamic;

public:
    IdentifierExpression(Expression *name, bool dynamic);

    Object *exec(Context *context);
};
