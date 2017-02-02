#pragma once

#include "expression.h"

class AttributeAssignmentExpression : public Expression {
    Expression *self;
    std::string name;
    Expression *value;

public:
    AttributeAssignmentExpression(Expression *self, const std::string &name, Expression *value);
    ~AttributeAssignmentExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
