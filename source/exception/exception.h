#pragma once
#include <common.h>

namespace Esther {

class Exception
{
public:
    virtual ~Exception();
    virtual void raise() = 0;
};

}
