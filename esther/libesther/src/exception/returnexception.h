#pragma once

#include "exception/valueexception.h"

namespace es {

class ReturnException : public ValueException {
public:
    ReturnException(Object *value);

    Object *value();

    void raise() override;
};
}
