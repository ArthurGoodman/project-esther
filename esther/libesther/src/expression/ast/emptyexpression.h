#pragma once

#include "expression/expression.h"

namespace es {

class EmptyExpression : public Expression {
protected:
    Object *exec(Esther *esther) override;
};
}
