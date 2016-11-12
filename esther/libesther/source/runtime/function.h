#pragma once

#include <vector>

#include "common/common.h"
#include "object.h"

class Function : public Object {
    std::string name;
    int arity;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Object *invoke(Object *self, const std::vector<Object *> &args);

    std::string toString() const;

protected:
    virtual Object *execute(Object *self, const std::vector<Object *> &args) = 0;

protected:
    Function(Class *objectClass, const std::string &name, int arity);
};
