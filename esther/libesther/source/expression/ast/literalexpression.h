#pragma once

#include "expression.h"
#include "variant.h"

class LiteralExpression : public Expression {
    Variant value;

public:
    LiteralExpression(const Variant &value);

protected:
    Ptr<Object> exec(Esther *esther) override;
};
