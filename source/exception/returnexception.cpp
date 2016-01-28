#include "returnexception.h"

ReturnException::ReturnException(IObject *value)
    : ValueException(value) {
}

IObject *ReturnException::value() {
    return getValue();
}

void ReturnException::raise() {
    throw this;
}
