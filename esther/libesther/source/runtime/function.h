#pragma once

#include <vector>

#include "common/common.h"
#include "object.h"

class Esther;

class Function : public Object {
    std::string *name;
    int arity;

public:
    ~Function();

    std::string getName() const;
    void setName(const std::string &name);

    Ptr<Object> invoke(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args);

    std::string toString() const;

protected:
    virtual Ptr<Object> execute(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) = 0;

protected:
    Function(Ptr<Class> objectClass, const std::string &name, int arity);
};
