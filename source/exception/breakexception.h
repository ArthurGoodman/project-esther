#pragma once

#include "valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(IObject *value);

    IObject *value();

    void raise();
};
