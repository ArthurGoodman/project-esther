#pragma once

#include "object.h"

class Context;

class Pattern : public Object {
protected:
    Pattern(const std::string &className);

public:
    virtual ~Pattern();

    virtual bool match(IObject *object, Context *context) = 0;
};
