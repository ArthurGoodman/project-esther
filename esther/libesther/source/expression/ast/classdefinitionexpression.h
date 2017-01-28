#pragma once

#include "expression.h"

class ClassDefinitionExpression : public Expression {
    std::string name;
    Expression *superclass, *body;

public:
    ClassDefinitionExpression(const std::string &name, Expression *superclass, Expression *body);
    ~ClassDefinitionExpression();

protected:
    Object *exec(Esther *esther);
};
