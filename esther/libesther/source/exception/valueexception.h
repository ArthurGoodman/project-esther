#pragma once

#include "exception.h"

class Object;

class ValueException : public Exception {
    Object *value;

protected:
    ValueException(Object *value);

    Object *getValue();
};
