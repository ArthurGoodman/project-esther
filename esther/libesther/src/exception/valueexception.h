#pragma once

#include "exception/exception.h"
#include "runtime/object.h"

namespace es {

class ValueException : public Exception {
    Object *volatile value;

protected:
    ValueException(Object *volatile value);

    Object *getValue();
};
}
