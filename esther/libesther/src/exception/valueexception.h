#pragma once

#include "exception/exception.h"
#include "runtime/object.h"

namespace es {

class ValueException : public Exception {
    Object *value;

protected:
    ValueException(Object *value);

    Object *getValue();
};
}
