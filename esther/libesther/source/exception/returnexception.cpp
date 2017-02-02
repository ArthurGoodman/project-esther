#include "returnexception.h"

ReturnException::ReturnException(Ptr<Object> value)
    : ValueException(value) {
}

Ptr<Object> ReturnException::value() {
    return getValue();
}

void ReturnException::raise() {
    throw this;
}
