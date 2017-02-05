#pragma once

#include "expression/expression.h"

namespace es {

class LocalAssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    LocalAssignmentExpression(const std::string &name, Expression *value);
    ~LocalAssignmentExpression();

protected:
    Object *exec(Esther *esther) override;
};
}
