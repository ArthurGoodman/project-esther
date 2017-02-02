#pragma once

#include "expression/expression.h"

class HereExpression : public Expression {
protected:
    Ptr<Object> exec(Esther *esther) override;
};
