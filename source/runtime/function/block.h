#pragma once
#include "common.h"

#include "object.h"

class Context;

class Block : public Object {
public:
    virtual Object *eval(Context *context) = 0;
};
