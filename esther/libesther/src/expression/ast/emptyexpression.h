#pragma once

#include "expression/expression.h"

class EmptyExpression : public Expression {
protected:
    Ptr<Object> exec(Esther *esther) override;
};
