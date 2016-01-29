#pragma once

#include "valueexception.h"

class ReturnException : public ValueException {
public:
    ReturnException(IObject *value);

    IObject *value();

    void raise();
};
