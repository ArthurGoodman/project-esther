#pragma once

#include "expression.h"

class StackExpression : public Expression {
    int index;

public:
    StackExpression(int index);

protected:
    Object *exec(Esther *esther);
};
