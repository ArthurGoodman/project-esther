#pragma once

#include "exception/exception.h"

namespace es {

class ContinueException : public Exception {
public:
    void raise() override;
};
}
