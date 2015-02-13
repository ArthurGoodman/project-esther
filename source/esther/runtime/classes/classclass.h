#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class ClassClass : public Class {
public:
    ClassClass();

    Object *newInstance();

    void setupMethods();
};
}
