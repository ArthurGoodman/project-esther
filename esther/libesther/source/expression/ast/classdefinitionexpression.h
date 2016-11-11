#pragma once

#include "expression.h"

class ClassDefinitionExpression : public Expression {
    std::string name;
    Expression *superclass;

public:
    ClassDefinitionExpression(const std::string &name, Expression *superclass);
    ~ClassDefinitionExpression();

    Object *exec(Context *context);
};
