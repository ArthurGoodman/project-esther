#pragma once

#include "expression/debug/debugexpression.h"
#include "variant/variant.h"

#if DEBUG_PARSER

class LiteralDebugExpression : public DebugExpression {
    Variant value;

public:
    LiteralDebugExpression(const Variant &value);

    std::string toString() const;
};

#endif
