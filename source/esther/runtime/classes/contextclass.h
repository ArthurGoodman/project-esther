#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class ContextClass : public Class {
public:
    ContextClass();

    Object *newInstance();

    void setupMethods();
};
}
