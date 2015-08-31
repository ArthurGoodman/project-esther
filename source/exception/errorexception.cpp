#include "errorexception.h"

ErrorException::ErrorException(string message, Position position)
    : PositionedObject(position), msg(message) {
}

string ErrorException::message() {
    return msg;
}
