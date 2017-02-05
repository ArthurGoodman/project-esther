#pragma once

#include <vector>

#include "common/common.h"
#include "runtime/object.h"

namespace es {

class Esther;

class Function : public Object {
    std::string name;
    int arity;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Object *invoke(Esther *esther, Object *self, const std::vector<Object *> &args);

    std::string toString() const;

protected:
    virtual Object *execute(Esther *esther, Object *self, const std::vector<Object *> &args) = 0;

protected:
    Function(Class *objectClass, const std::string &name, int arity);
};
}
