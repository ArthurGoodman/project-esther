#include "exception/valueexception.h"

namespace es {

ValueException::ValueException(Ptr<Object> value)
    : value(value) {
}

Ptr<Object> ValueException::getValue() {
    return value;
}
}
