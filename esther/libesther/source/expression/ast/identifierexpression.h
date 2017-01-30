#pragma once

#include "expression.h"

class IdentifierExpression : public Expression {
    std::string name;

public:
    IdentifierExpression(const std::string &name);
    ~IdentifierExpression();

protected:
    Pointer<Object> exec(Esther *esther);
};
