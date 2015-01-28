#include "returnexception.h"

namespace esther {

ReturnException::ReturnException(Object *value)
    : ValueException(value) {
}

Object *ReturnException::value() {
    return getValue();
}

void ReturnException::raise() {
    throw this;
}
}
