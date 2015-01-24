#pragma once
#include <common.h>

#include "object.h"

namespace esther {

class Null : public Object {
public:
    Null();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string toString();
};
}
