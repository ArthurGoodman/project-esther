#pragma once

#include "expression/expression.h"

namespace es {

class AttributeAssignmentExpression : public Expression {
    Expression *self;
    std::string name;
    Expression *value;

public:
    AttributeAssignmentExpression(Expression *self, const std::string &name, Expression *value);
    ~AttributeAssignmentExpression();

protected:
    Object *exec(Esther *esther) override;
};
}
