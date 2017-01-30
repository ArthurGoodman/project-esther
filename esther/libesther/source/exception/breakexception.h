#pragma once

#include "valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(Pointer<Object> value);

    Pointer<Object> value();

    void raise();
};
