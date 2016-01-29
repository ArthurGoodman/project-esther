#pragma once

#include "debug.h"
#include "expression.h"

#if DEBUG_PARSER

class DebugExpression : public Expression {
    std::string name;
    std::list<IObject *> args;

    static int indent;

public:
    DebugExpression(const std::string &name, std::list<IObject *> args = std::list<IObject *>());

    IObject *exec(Context *context);

    std::string toString();
};

#endif
