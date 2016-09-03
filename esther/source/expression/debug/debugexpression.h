#pragma once

#include "debug.h"
#include "expression.h"

#include <string>
#include <list>

#if DEBUG_PARSER

class DebugExpression : public Expression {
    std::string name;
    std::list<Object *> args;

    static int indent;

public:
    DebugExpression(const std::string &name, std::list<Object *> args = std::list<Object *>());

    Object *exec(Context *context);

    std::string toString();
};

#endif
