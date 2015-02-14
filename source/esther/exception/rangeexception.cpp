#include "rangeexception.h"

namespace esther {

RangeException::RangeException()
    : Exception("index out of range") {
}

void RangeException::raise() {
    throw this;
}
}
