#include "exception.h"

namespace esther {

Exception::Exception(string message)
    : msg(message) {
}

Exception::~Exception() {
}

string Exception::message() {
    return msg;
}
}
