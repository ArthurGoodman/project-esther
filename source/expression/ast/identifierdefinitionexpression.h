#pragma once

#include "identifierexpression.h"

class IdentifierDefinitionExpression : public IdentifierExpression {
    Expression *type, *value;

public:
    IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value, bool dynamic);

    void setValue(Expression *value);

    IObject *exec(Context *context);
};
