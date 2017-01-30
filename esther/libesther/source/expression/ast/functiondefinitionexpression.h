#pragma once

#include "expression.h"

class FunctionDefinitionExpression : public Expression {
    std::string name;
    std::list<std::string> params;
    Expression *body;

public:
    FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body);
    ~FunctionDefinitionExpression();

protected:
    Pointer<Object> exec(Esther *esther);
};
