#pragma once
#include <common.h>

#include "method.h"
#include "interpretedfunction.h"

namespace Esther {

class InterpretedMethod : public Method, public InterpretedFunction
{
public:
};

}
