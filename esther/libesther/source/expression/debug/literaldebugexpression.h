#pragma once

#include "debugexpression.h"
#include "variant.h"

#if DEBUG_PARSER

class LiteralDebugExpression : public DebugExpression {
    Variant value;

public:
    LiteralDebugExpression(const Variant &value);

    std::string toString() const;
};

#endif
