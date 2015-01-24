#pragma once
#include <common.h>

#include "object.h"

namespace esther {

class Class : public Object {
    string name;

public:
    Class(string name);

    string getName();

    string toString();
};
}
