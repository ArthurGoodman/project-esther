#pragma once

#include "expression/expression.h"

namespace es {

class AssignmentExpression : public Expression {
    std::string name;
    Expression *value;

public:
    AssignmentExpression(const std::string &name, Expression *value);
    ~AssignmentExpression();

protected:
    Object *exec(Esther *esther) override;
};
}
