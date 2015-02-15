#pragma once
#include "common.h"

#include "expression.h"

class ClassExpression : public Expression {
    Expression *name, *superclass, *body;

public:
    ClassExpression(Expression *name, Expression *superclass, Expression *body);

    Object *eval(Context *context);
};
