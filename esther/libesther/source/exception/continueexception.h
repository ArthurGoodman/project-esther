#pragma once

#include "exception.h"

class ContinueException : public Exception {
public:
    void raise() override;
};
