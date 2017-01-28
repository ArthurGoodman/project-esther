#pragma once

#include "expression.h"

class CallExpression : public Expression {
    std::string name;
    std::list<Expression *> args;

public:
    CallExpression(const std::string &name, const std::list<Expression *> &args);
    ~CallExpression();

    Object *exec(Esther *esther);
};
