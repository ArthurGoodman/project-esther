#include "breakexception.h"

BreakException::BreakException(Ptr<Object> value)
    : ValueException(value) {
}

void BreakException::raise() {
    throw this;
}
