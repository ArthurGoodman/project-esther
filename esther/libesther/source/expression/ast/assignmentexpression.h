#pragma once

#include "expression.h"

class AssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    AssignmentExpression(const std::string &name, Expression *value);
    ~AssignmentExpression();

protected:
    Object *exec(Context *context);
};