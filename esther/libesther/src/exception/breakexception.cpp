#include "exception/breakexception.h"

namespace es {

BreakException::BreakException(Object *value)
    : ValueException(value) {
}

void BreakException::raise() {
    throw this;
}
}
