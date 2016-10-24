#include "runtimeerror.h"

RuntimeError::RuntimeError(const std::string &message)
    : ErrorException(message) {
}

std::string RuntimeError::message() {
    return "runtime error: " + ErrorException::message();
}

void RuntimeError::raise() {
    throw this;
}
