#pragma once

#include "expression.h"

class IdentifierExpression : public Expression {
    std::string name;

public:
    IdentifierExpression(const std::string &name);
    ~IdentifierExpression();

    Object *exec(Context *context);
};
