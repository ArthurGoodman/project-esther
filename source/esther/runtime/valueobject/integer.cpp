#include "integer.h"

namespace esther {

Integer::Integer(int value)
    : ValueObject(value) {
}

Integer::Integer()
    : ValueObject(0) {
}
}
