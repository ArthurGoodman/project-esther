#pragma once
#include "common.h"

#include "expression.h"

class IdentifierExpression : public Expression {
protected:
    Expression *name;
    bool dynamic;

public:
    IdentifierExpression(Expression *name, bool dynamic);

    Expression *getName();
    bool isDynamic();

    IObject *exec(Context *context);
};
