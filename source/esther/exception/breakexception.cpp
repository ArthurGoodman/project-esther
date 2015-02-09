#include "breakexception.h"

namespace esther {

BreakException::BreakException(Object *value)
    : ValueException(value) {
}

Object *BreakException::value() {
    return getValue();
}

void BreakException::raise() {
    throw this;
}
}
