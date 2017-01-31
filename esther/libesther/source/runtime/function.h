#pragma once

#include <vector>

#include "common/common.h"
#include "object.h"

class Esther;

class Function : public Object {
    std::string name;
    int arity;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Pointer<Object> invoke(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);

    std::string toString() const;

protected:
    virtual Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) = 0;

protected:
    Function(Pointer<Class> objectClass, const std::string &name, int arity);
};
