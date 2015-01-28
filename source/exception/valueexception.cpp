#include "valueexception.h"

namespace esther {

ValueException::ValueException(Object *value)
    : value(value) {
}

Object *ValueException::getValue() {
    return value;
}
}
