#pragma once
#include <common.h>

#include "errorexception.h"

namespace esther {

class RuntimeError : public ErrorException {
public:
    RuntimeError(string message);

    string msg();

    void raise();
};
}
