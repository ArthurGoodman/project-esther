#pragma once

#include "expression/expression.h"

namespace es {

class AttributeExpression : public Expression {
    Expression *self;
    std::string name;

public:
    AttributeExpression(Expression *self, const std::string &name);
    ~AttributeExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}
