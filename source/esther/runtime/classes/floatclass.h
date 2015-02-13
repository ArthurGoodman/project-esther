#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class FloatClass : public Class {
public:
    FloatClass();

    Object *newInstance();

    void setupMethods();
};
}
