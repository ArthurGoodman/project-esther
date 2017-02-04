#pragma once

#include <string>
#include <list>

#include "common/common.h"
#include "expression/expression.h"

#ifdef DEBUG_EXPRESSION

namespace es {

class DebugExpression : public Expression {
    friend class DebugExpressionManager;

    std::string name;
    std::list<DebugExpression *> args;

protected:
    static int indent;

public:
    DebugExpression(const std::string &name, const std::list<DebugExpression *> &args = std::list<DebugExpression *>());
    ~DebugExpression();

    Ptr<Object> exec(Esther *esther) override;

    virtual std::string toString() const;
};
}

#endif
