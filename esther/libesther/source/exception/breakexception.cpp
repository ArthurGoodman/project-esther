#include "breakexception.h"

BreakException::BreakException(Pointer<Object> value)
    : ValueException(value) {
}

void BreakException::raise() {
    throw this;
}
