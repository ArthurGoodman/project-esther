#pragma once

#include <string>
#include <list>

#include "common.h"
#include "expression.h"

#if DEBUG_PARSER

class DebugExpression : public Expression {
    std::string name;
    std::list<DebugExpression *> args;

    static int indent;

public:
    DebugExpression(const std::string &name, std::list<DebugExpression *> args = std::list<DebugExpression *>());

    Object *exec(Context *context);

    std::string toString();
};

#endif
