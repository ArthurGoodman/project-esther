#pragma once

#include "exception.h"
#include "object.h"

class ValueException : public Exception {
    Pointer<Object> value;

protected:
    ValueException(Pointer<Object> value);

    Pointer<Object> getValue();
};
