#pragma once
#include "common.h"

#include "debug.h"
#include "expression.h"

#if DEBUG_PARSER

class DebugExpression : public Expression {
    string name;
    list<Object *> args;

    static int indent;

public:
    DebugExpression(string name, list<Object *> args = list<Object *>());

    Object *exec(Context *context);

    string immediateToString();
};

#endif
