#pragma once
#include "common.h"

#include "valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(IObject *value);

    IObject *value();

    void raise();
};
