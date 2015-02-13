#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class StringClass : public Class {
public:
    StringClass();

    Object *newInstance();

    void setupMethods();
};
}
