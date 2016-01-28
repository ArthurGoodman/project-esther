#pragma once
#include "common.h"

#include "valueexception.h"

class ReturnException : public ValueException {
public:
    ReturnException(IObject *value);

    IObject *value();

    void raise();
};
