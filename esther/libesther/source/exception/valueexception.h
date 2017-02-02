#pragma once

#include "exception.h"
#include "object.h"

class ValueException : public Exception {
    Ptr<Object> value;

protected:
    ValueException(Ptr<Object> value);

    Ptr<Object> getValue();
};
