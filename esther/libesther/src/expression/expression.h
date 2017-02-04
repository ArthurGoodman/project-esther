#pragma once

#include <list>

#include "common/config.h"
#include "common/position.h"

#include "expression/expressionmanager.h"
#include "expression/debug/debugexpressionmanager.h"

namespace es {

class Esther;

class Expression : public
#ifdef DEBUG_EXPRESSION
                   DebugExpressionManager
#else
                   ExpressionManager
#endif
{
    Position position;

public:
    virtual ~Expression();

    Ptr<Object> eval(Esther *esther);

    Position getPosition() const;
    void setPosition(Position position);

protected:
    virtual Ptr<Object> exec(Esther *esther) = 0;
};
}
