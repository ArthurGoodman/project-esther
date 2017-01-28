#pragma once

#include "expression.h"

class LocalAssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    LocalAssignmentExpression(const std::string &name, Expression *value);
    ~LocalAssignmentExpression();

    Object *exec(Esther *esther);
};
