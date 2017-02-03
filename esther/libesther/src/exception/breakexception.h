#pragma once

#include "exception/valueexception.h"

namespace es {

class BreakException : public ValueException {
public:
    BreakException(Ptr<Object> value);

    void raise() override;
};
}
