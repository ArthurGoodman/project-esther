#pragma once

#include "exception/exception.h"

class ContinueException : public Exception {
public:
    void raise() override;
};
