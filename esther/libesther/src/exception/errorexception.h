#pragma once

#include "exception/exception.h"
#include "common/position.h"

class ErrorException : public Exception {
    Position position;
    std::string msg;

public:
    ErrorException(const std::string &message, Position position = Position());

    std::string message() override;

    Position getPosition();
    void setPosition(Position position);
};
