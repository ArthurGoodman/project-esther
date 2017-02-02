#pragma once

#include "expression/expression.h"

class AssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    AssignmentExpression(const std::string &name, Expression *value);
    ~AssignmentExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
