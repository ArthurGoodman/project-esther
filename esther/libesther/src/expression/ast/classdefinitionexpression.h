#pragma once

#include "expression/expression.h"

class ClassDefinitionExpression : public Expression {
    std::string name;
    Expression *superclass;

public:
    ClassDefinitionExpression(const std::string &name, Expression *superclass);
    ~ClassDefinitionExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
