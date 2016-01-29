#pragma once

#include "exception.h"

class MatchFailureException : public Exception {
public:
    std::string message();
    void raise();
};
