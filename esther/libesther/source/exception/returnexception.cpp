#include "returnexception.h"

ReturnException::ReturnException(Pointer<Object> value)
    : ValueException(value) {
}

Pointer<Object> ReturnException::value() {
    return getValue();
}

void ReturnException::raise() {
    throw this;
}
