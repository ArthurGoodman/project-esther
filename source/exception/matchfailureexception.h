#pragma once
#include "common.h"

#include "exception.h"

class MatchFailureException : public Exception {
public:
    string message();
    void raise();
};
