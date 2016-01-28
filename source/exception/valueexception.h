#pragma once
#include "common.h"

#include "exception.h"

class IObject;

class ValueException : public Exception {
    IObject *value;

protected:
    ValueException(IObject *value);

    IObject *getValue();
};
