#pragma once
#include <common.h>

namespace Esther {

class Expression;

class ExpressionManager
{
public:
    enum ExpressionType
    {
    };

public:
    virtual ~ExpressionManager();
    virtual Expression *create(ExpressionType type) = 0;
};

}
