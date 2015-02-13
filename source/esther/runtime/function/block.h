#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Context;

class Block : public Object {
public:
    virtual Object *eval(Context *context) = 0;
};
}
