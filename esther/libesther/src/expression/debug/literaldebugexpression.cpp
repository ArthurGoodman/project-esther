#include "expression/debug/literaldebugexpression.h"

#if DEBUG_PARSER

namespace es {

LiteralDebugExpression::LiteralDebugExpression(const Variant &value)
    : DebugExpression("")
    , value(value) {
}

std::string LiteralDebugExpression::toString() const {
    std::string spacing;
    spacing.insert(0, 4 * indent, ' ');

    return spacing + value.toString();
}
}

#endif
