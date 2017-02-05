#pragma once

#include "exception/valueexception.h"

namespace es {

class BreakException : public ValueException {
public:
    BreakException(Object *value);

    void raise() override;
};
}
