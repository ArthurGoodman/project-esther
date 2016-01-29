#pragma once

#include "object.h"

class Context;

class Block : public Object {
public:
    Block();

    virtual IObject *eval(Context *context) = 0;
};
