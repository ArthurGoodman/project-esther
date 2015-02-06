#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class True : public Object {
public:
    True();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string toString();
};
}
