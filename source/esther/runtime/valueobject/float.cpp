#include "float.h"

namespace esther {

Float::Float(double value)
    : ValueObject(value) {
}

Float::Float()
    : ValueObject(0.) {
}
}
