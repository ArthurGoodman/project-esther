#pragma once

#include "expression.h"

class FunctionDefinitionExpression : public Expression {
    std::string name;
    std::list<std::string> params;
    Expression *body;
    Context *context;

public:
    FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);
    ~FunctionDefinitionExpression();

    Object *exec(Context *context);
};