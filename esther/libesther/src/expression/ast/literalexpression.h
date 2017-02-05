#pragma once

#include "expression/expression.h"
#include "variant/variant.h"

namespace es {

class LiteralExpression : public Expression {
    Variant value;

public:
    LiteralExpression(const Variant &value);

protected:
    Object *exec(Esther *esther) override;
};
}
