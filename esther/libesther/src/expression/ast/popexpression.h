#pragma once

#include "expression/expression.h"

class PopExpression : public Expression {
   int count;

public:
    PopExpression(int count);

protected:
    Ptr<Object> exec(Esther *esther) override;
};