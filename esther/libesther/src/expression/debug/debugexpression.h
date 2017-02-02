#pragma once

#include <string>
#include <list>

#include "common/common.h"
#include "expression/expression.h"

#if DEBUG_PARSER

class DebugExpression : public Expression {
    std::string name;
    std::list<DebugExpression *> args;

protected:
    static int indent;

public:
    DebugExpression(const std::string &name, const std::list<DebugExpression *> &args = std::list<DebugExpression *>());
    ~DebugExpression();

    Object *exec(Esther *esther);

    virtual std::string toString() const;
};

#endif
