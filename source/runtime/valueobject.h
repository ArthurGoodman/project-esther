#pragma once
#include <common.h>

#include "object.h"
#include "variant.h"

namespace esther {

class ValueObject : public Object {
    Variant value;

public:
    ValueObject(int value);
    ValueObject(double value);
    ValueObject(char value);
    ValueObject(string value);
    ValueObject(const char *value);

    string toString();
};
}
