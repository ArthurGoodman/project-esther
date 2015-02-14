#pragma once
#include "common.h"

#include "exception.h"

namespace esther {

class RangeException : public Exception {
public:
    RangeException();

    void raise();
};
}
