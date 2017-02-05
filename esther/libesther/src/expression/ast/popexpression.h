#pragma once

#include "expression/expression.h"

namespace es {

class PopExpression : public Expression {
    int count;

public:
    PopExpression(int count);

protected:
    Object *exec(Esther *esther) override;
};
}
