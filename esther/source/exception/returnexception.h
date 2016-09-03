#pragma once

#include "valueexception.h"

class ReturnException : public ValueException {
public:
    ReturnException(Object *value);

    Object *value();

    void raise();
};
