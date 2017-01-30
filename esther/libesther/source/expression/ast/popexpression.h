#pragma once

#include "expression.h"

class PopExpression : public Expression {
   int count;

public:
    PopExpression(int count);

protected:
    Object *exec(Esther *esther);
};
