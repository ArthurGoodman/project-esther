#include "exception/valueexception.h"

namespace es {

ValueException::ValueException(Object *value)
    : value(value) {
}

Object *ValueException::getValue() {
    return value;
}
}
