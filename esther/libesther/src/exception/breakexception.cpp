#include "exception/breakexception.h"

namespace es {

BreakException::BreakException(Object *volatile value)
    : ValueException(value) {
}

void BreakException::raise() {
    throw this;
}
}
