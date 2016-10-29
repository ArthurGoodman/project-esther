#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    std::string name;
    Class *superclass;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Object *newInstance();

protected:
    virtual Object *createNewInstance();
};
