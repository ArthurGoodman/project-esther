#pragma once

#include "errorexception.h"

class RuntimeError : public ErrorException {
public:
    RuntimeError(const std::string &message);

    std::string message();
    void raise();
};