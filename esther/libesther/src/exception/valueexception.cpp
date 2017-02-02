#include "valueexception.h"

ValueException::ValueException(Ptr<Object> value)
    : value(value) {
}

Ptr<Object> ValueException::getValue() {
    return value;
}
