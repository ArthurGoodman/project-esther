#pragma once

#include "expression/expression.h"

namespace es {

class FunctionDefinitionExpression : public Expression {
    std::string name;
    std::list<std::string> params;
    Expression *body;

public:
    FunctionDefinitionExpression(const std::string &name, const std::list<std::string> &params, Expression *body);
    ~FunctionDefinitionExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}
