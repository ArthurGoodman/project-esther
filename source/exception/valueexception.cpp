#include "valueexception.h"

ValueException::ValueException(IObject *value)
    : value(value) {
}

IObject *ValueException::getValue() {
    return value;
}
