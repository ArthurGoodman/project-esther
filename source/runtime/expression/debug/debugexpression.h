#pragma once
#include <common.h>
#include <debug.h>

#include "expression.h"

#if DEBUG_PARSER

namespace esther {

class DebugExpression : public Expression {
    string name;
    list<Object *> args;

    static int indent;

public:
    DebugExpression(string name, list<Object *> args = list<Object *>());

    Object *eval(Context *context);

    string toString();
};
}

#endif
