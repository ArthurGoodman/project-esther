#pragma once

#include "expression/expression.h"

namespace es {

class HereExpression : public Expression {
protected:
    Ptr<Object> exec(Esther *esther) override;
};
}
