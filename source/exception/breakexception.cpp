#include "breakexception.h"

BreakException::BreakException(Object *value)
    : ValueException(value) {
}

Object *BreakException::value() {
    return getValue();
}

void BreakException::raise() {
    throw this;
}
