#pragma once

#include "expression.h"

class ClassExpression : public Expression {
    Expression *name, *superclass, *body;

public:
    ClassExpression(Expression *name, Expression *superclass, Expression *body);

    IObject *exec(Context *context);
};
