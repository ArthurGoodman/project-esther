#pragma once

#include "expression.h"

class PopExpression : public Expression {
   int count;

public:
    PopExpression(int count);

protected:
    Pointer<Object> exec(Esther *esther) override;
};
