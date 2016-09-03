#pragma once

#include "errorexception.h"

class LexicalError : public ErrorException {
public:
    LexicalError(const std::string &message, Position getPosition);

    std::string message();
    void raise();
};
