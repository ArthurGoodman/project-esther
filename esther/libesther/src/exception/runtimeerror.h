#pragma once

#include "exception/errorexception.h"

class RuntimeError : public ErrorException {
public:
    RuntimeError(const std::string &message);

    std::string message() override;
    void raise() override;
};
