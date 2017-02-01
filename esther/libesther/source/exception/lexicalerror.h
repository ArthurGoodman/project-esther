#pragma once

#include "errorexception.h"

class LexicalError : public ErrorException {
public:
    LexicalError(const std::string &message, Position position);

    std::string message() override;
    void raise() override;
};
