#pragma once

#include "exception/valueexception.h"

namespace es {

class BreakException : public ValueException {
public:
    BreakException(Object *volatile value);

    void raise() override;
};
}
