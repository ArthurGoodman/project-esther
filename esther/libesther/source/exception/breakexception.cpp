#include "breakexception.h"

BreakException::BreakException(Pointer<Object> value)
    : ValueException(value) {
}

Pointer<Object> BreakException::value() {
    return getValue();
}

void BreakException::raise() {
    throw this;
}
