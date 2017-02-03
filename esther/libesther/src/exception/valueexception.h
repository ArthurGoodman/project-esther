#pragma once

#include "exception/exception.h"
#include "runtime/object.h"

namespace es {

class ValueException : public Exception {
    Ptr<Object> value;

protected:
    ValueException(Ptr<Object> value);

    Ptr<Object> getValue();
};
}
