#pragma once
#include <common.h>
#include <debug.h>

#include "expression.h"

#if DEBUG_EXPRESSIONS

namespace esther {

class DebugExpression : public Expression {
    string name;

public:
    DebugExpression(string name);

    Object *eval(Context *context);
};
}

#endif
