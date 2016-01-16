#pragma once
#include "common.h"

#include "identifierexpression.h"

class IdentifierDefinitionExpression : public IdentifierExpression {
    Expression *type, *value;

public:
    IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value, bool dynamic);

    void setValue(Expression *value);

    Object *exec(Context *context);
};
