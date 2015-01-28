#pragma once
#include <common.h>

#include "valueexception.h"

namespace esther {

class ReturnException : public ValueException {
public:
    ReturnException(Object *value);

    Object *value();

    void raise();
};
}
