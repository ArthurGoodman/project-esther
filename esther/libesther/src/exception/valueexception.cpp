#include "exception/valueexception.h"

namespace es {

ValueException::ValueException(Object *volatile value)
    : value(value) {
}

Object *ValueException::getValue() {
    return value;
}
}
