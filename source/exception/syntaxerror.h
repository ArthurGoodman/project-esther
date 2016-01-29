#pragma once

#include "errorexception.h"

class SyntaxError : public ErrorException {
public:
    SyntaxError(const std::string &message, Position getPosition);

    std::string message();
    void raise();
};
