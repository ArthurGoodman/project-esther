#pragma once
#include "common.h"

#include "exception.h"
#include "position.h"
#include "positionedobject.h"

class ErrorException : public Exception, public PositionedObject {
    string msg;

public:
    ErrorException(string message, Position position = Position());

    string message();
};
