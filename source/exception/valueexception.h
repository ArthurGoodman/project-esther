#pragma once
#include "common.h"

#include "exception.h"

namespace esther {

class Object;

class ValueException : public Exception {
    Object *value;

protected:
    ValueException(Object *value);

    Object *getValue();
};
}
