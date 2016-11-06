#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    friend class ClassClass;

    std::string name;
    Class *superclass;

public:
    std::string getName() const;
    void setName(const std::string &name);

    Class *getSuperclass() const;
    void setSuperclass(Class *superclass);

    Object *newInstance();

    std::string toString() const;

    Object *lookup(const std::string &name) const;

protected:
    Class(Class *objectClass, const std::string &name, Class *superclass);

    virtual Object *createNewInstance();
};
