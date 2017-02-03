#pragma once

#include "exception/errorexception.h"

namespace es {

class RuntimeError : public ErrorException {
public:
    RuntimeError(const std::string &message);

    std::string message() override;
    void raise() override;
};
}
