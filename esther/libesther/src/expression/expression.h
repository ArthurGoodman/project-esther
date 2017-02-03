#pragma once

#include <list>

#include "expression/expressionmanager.h"
#include "expression/debug/debugexpressionmanager.h"
#include "common/position.h"

class Esther;

class Expression : public
#if DEBUG_PARSER
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