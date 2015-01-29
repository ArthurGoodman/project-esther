#include "runtimeerror.h"

namespace esther {

RuntimeError::RuntimeError(string message)
    : ErrorException(message) {
}

string RuntimeError::msg() {
    return "runtime error: " + ErrorException::msg();
}

void RuntimeError::raise() {
    throw this;
}
}
