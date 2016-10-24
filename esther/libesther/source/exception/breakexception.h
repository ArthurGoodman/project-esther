#pragma once

#include "valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(Object *value);

    Object *value();

    void raise();
};
