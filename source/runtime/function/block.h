#pragma once
#include "common.h"

#include "object.h"

class Context;

class Block : public Object {
public:
    Block();

    virtual Object *eval(Context *context) = 0;
};
