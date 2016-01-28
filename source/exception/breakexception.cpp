#include "breakexception.h"

BreakException::BreakException(IObject *value)
    : ValueException(value) {
}

IObject *BreakException::value() {
    return getValue();
}

void BreakException::raise() {
    throw this;
}
