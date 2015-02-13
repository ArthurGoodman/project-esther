#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class MethodClass : public Class {
public:
    MethodClass();

    Object *newInstance();

    void setupMethods();
};
}
