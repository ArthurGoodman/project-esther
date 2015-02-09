#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class False : public Object {
public:
    False();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string toString();
};
}
