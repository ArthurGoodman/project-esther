#pragma once

#include "expression/expression.h"

namespace es {

class ConstantExpression : public Expression {
    Object *value;

public:
    ConstantExpression(Object *value);

protected:
    Object *exec(Esther *esther) override;
};
}
