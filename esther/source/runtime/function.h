#pragma once

#include <list>

#include "common.h"
#include "object.h"

class Function : public Object {
    std::string name;
    uint arity;

public:
    Function(const std::string &name, uint arity);

    std::string getName() const;

    Object *invoke(Object *self, const std::list<Object *> &args);
    virtual Object *execute(Object *self, const std::list<Object *> &args) = 0;
};
