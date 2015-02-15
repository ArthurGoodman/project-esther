#pragma once
#include "common.h"

#include "exception.h"

class Object;

class ValueException : public Exception {
    Object *value;

protected:
    ValueException(Object *value);

    Object *getValue();
};
