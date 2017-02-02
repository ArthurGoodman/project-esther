#pragma once

#include "exception/valueexception.h"

class BreakException : public ValueException {
public:
    BreakException(Ptr<Object> value);

    void raise() override;
};
