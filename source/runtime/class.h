#pragma once

#include "object.h"

class Method;

class Class : public Object {
protected:
    std::string name;
    Class *superclass;

public:
    Class(const std::string &name, Class *superclass);
    Class(const std::string &name, const std::string &superclassName);
    Class(const std::string &name);

    std::string getName();

    Class *getSuperclass();
    void setSuperclass(Class *superclass);

    bool isChild(Class *_class);

    IObject *newInstance();
    IObject *newInstance(Tuple *args);

    bool hasMethod(const std::string &name);
    Method *getMethod(const std::string &name);
    void setMethod(Method *method);
    void setMethod(const std::string &name, Method *method);

    IObject *lookup(const std::string &name);

    IObject *call(const std::string &name, Tuple *args);

    std::string toString();

protected:
    virtual IObject *createNewInstance();
};
