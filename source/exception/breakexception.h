#pragma once
#include "common.h"

#include "valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(Object *value);

    Object *value();

    void raise();
};
