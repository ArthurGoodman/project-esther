#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class IntegerClass : public Class {
public:
    IntegerClass();

    Object *newInstance();

    void setupMethods();
};
}
