#include "debugexpression.h"

#if DEBUG_EXPRESSIONS

namespace esther {

DebugExpression::DebugExpression(string name)
    : name(name) {
}

Object *DebugExpression::eval(Context *) {
    return 0;
}
}

#endif
