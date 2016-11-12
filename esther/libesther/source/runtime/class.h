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

    Object *newInstance(const std::vector<Object *> &args = std::vector<Object *>());

    bool isChild(Class *_class) const;

    std::string toString() const;

    Object *lookup(const std::string &name) const;

protected:
    Class(Class *classClass, const std::string &name, Class *superclass);

    virtual Object *createNewInstance(const std::vector<Object *> &args);
};
