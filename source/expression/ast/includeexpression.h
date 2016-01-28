#pragma once
#include "common.h"

#include "expression.h"

class IncludeExpression : public Expression {
    Expression *fileName;

public:
    IncludeExpression(Expression *fileName);

    IObject *exec(Context *context);
};
