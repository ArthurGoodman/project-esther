#pragma once

#include "expression.h"

class NativeCallExpression : public Expression {
    Object *(*f)();
    std::list<Expression *> args;

public:
    NativeCallExpression(Object *(*f)(Context *...), const std::list<Expression *> &args);
    ~NativeCallExpression();

    Object *exec(Context *context);
};
