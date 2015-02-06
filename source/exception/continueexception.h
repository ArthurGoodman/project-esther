#pragma once
#include "common.h"

#include "exception.h"

namespace esther {

class ContinueException : public Exception {
public:
    void raise();
};
}
