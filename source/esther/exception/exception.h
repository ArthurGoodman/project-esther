#pragma once
#include "common.h"

namespace esther {

class Exception {
public:
    virtual ~Exception();

    virtual void raise() = 0;
};
}
