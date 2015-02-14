#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class TupleClass : public Class {
public:
    TupleClass();

    Object *newInstance();

    void setupMethods();
};
}
