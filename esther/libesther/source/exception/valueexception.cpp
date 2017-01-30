#include "valueexception.h"

ValueException::ValueException(Pointer<Object> value)
    : value(value) {
}

Pointer<Object> ValueException::getValue() {
    return value;
}
