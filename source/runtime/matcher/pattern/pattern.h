#pragma once
#include "common.h"

#include "object.h"

class Pattern : public Object {
public:
    virtual ~Pattern();

    virtual bool match(Object *object) = 0;
};
