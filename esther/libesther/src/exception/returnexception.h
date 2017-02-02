#pragma once

#include "exception/valueexception.h"

class ReturnException : public ValueException {
public:
    ReturnException(Ptr<Object> value);

    Ptr<Object> value();

    void raise() override;
};
