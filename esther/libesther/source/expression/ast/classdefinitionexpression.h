#pragma once

#include "expression.h"

class ClassDefinitionExpression : public Expression {
    std::string name;
    Expression *superclass;

public:
    ClassDefinitionExpression(const std::string &name, Expression *superclass);
    ~ClassDefinitionExpression();

protected:
    Pointer<Object> exec(Esther *esther) override;
};
