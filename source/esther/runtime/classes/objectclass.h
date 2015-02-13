#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class ObjectClass : public Class {
public:
    ObjectClass();

    Object *newInstance();

    void setupMethods();
};
}
