#pragma once

#include "expression/expression.h"

namespace es {

class ConstantExpression : public Expression {
    Object *value;

public:
    ConstantExpression(Object *volatile value);

protected:
    Object *exec(Esther *esther) override;
};
}
