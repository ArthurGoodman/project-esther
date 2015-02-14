#include "runtimeerror.h"

namespace esther {

RuntimeError::RuntimeError(string message)
    : ErrorException(message) {
}

string RuntimeError::message() {
    return "runtime error: " + ErrorException::message();
}

void RuntimeError::raise() {
    throw this;
}
}
