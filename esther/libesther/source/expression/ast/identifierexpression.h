#pragma once

#include "expression.h"

class IdentifierExpression : public Expression {
    std::string name;

public:
    IdentifierExpression(const std::string &name);
    ~IdentifierExpression();

protected:
    Object *exec(Esther *esther);
};
