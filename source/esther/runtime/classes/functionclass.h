#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class FunctionClass : public Class {
public:
    FunctionClass();

    Object *newInstance();

    void setupMethods();
};
}
