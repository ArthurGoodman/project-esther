#pragma once

#include <list>

#include "common.h"
#include "object.h"

class Function : public Object {
    std::string name;
    uint arity;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Object *invoke(Object *self, const std::list<Object *> &args);
    virtual Object *execute(Object *self, const std::list<Object *> &args) = 0;

    std::string toString() const;

protected:
    Function(Class *objectClass, const std::string &name, uint arity);
};
