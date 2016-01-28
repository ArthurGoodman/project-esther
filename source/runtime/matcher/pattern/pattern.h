#pragma once
#include "common.h"

#include "object.h"

class Context;

class Pattern : public Object {
protected:
    Pattern(string className);

public:
    virtual ~Pattern();

    virtual bool match(IObject *object, Context *context) = 0;
};
