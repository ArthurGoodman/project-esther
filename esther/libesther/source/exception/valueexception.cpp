#include "valueexception.h"

ValueException::ValueException(Object *value)
    : value(value) {
}

Object *ValueException::getValue() {
    return value;
}
