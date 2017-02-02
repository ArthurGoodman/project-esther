#pragma once

#include "expression/expression.h"

class IdentifierExpression : public Expression {
    std::string name;

public:
    IdentifierExpression(const std::string &name);
    ~IdentifierExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
