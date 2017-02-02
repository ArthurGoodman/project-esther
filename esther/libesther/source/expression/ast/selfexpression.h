#pragma once

#include "expression.h"

class SelfExpression : public Expression {
protected:
    Ptr<Object> exec(Esther *esther) override;
};
