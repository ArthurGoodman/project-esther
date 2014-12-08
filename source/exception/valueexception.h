#pragma once
#include <common.h>

#include "exception.h"

namespace Esther {

class Object;

class ValueException : public Exception {
    Object *value;

public:
};
}
