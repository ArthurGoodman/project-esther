#pragma once

#include "expression/debug/debugexpression.h"
#include "variant/variant.h"

#ifdef DEBUG_EXPRESSION

namespace es {

class LiteralDebugExpression : public DebugExpression {
    Variant value;

public:
    LiteralDebugExpression(const Variant &value);

    std::string toString() const override;
};
}

#endif
