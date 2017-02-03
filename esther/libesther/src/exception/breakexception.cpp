#include "exception/breakexception.h"

namespace es {

BreakException::BreakException(Ptr<Object> value)
    : ValueException(value) {
}

void BreakException::raise() {
    throw this;
}
}
