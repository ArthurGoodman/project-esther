#pragma once

#include "expression.h"

class LocalAssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    LocalAssignmentExpression(const std::string &name, Expression *value);
    ~LocalAssignmentExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
