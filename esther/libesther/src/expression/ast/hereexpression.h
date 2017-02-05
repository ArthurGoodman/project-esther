#pragma once

#include "expression/expression.h"

namespace es {

class HereExpression : public Expression {
protected:
    Object *exec(Esther *esther) override;
};
}
