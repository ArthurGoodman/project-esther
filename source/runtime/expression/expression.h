#pragma once
#include <common.h>

#include "object.h"

namespace Esther {

class ExpressionManager;

class Expression : public Object
{
    friend class EstherEngine;

    static ExpressionManager *manager;

public:
};

}
