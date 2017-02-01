#pragma once

#include "valueexception.h"

class ReturnException : public ValueException {
public:
    ReturnException(Pointer<Object> value);

    Pointer<Object> value();

    void raise() override;
};
