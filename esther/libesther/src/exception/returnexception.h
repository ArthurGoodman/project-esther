#pragma once

#include "exception/valueexception.h"

namespace es {

class ReturnException : public ValueException {
public:
    ReturnException(Object *volatile value);

    Object *value();

    void raise() override;
};
}
