#include "errorexception.h"

namespace Esther {

ErrorException::ErrorException(string msg, Position pos) : message(msg), position(pos) {}

string ErrorException::msg() { return message; }
Position ErrorException::pos() { return position; }

}
