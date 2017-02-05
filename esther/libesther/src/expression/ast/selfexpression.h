#pragma once

#include "expression/expression.h"

namespace es {

class SelfExpression : public Expression {
protected:
    Object *exec(Esther *esther) override;
};
}
