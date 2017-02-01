#pragma once

#include "errorexception.h"

class SyntaxError : public ErrorException {
public:
    SyntaxError(const std::string &message, Position position);

    std::string message() override;
    void raise() override;
};
