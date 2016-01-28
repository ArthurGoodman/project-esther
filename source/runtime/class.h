#pragma once
#include "common.h"

#include "object.h"

class Method;

class Class : public Object {
protected:
    string name;
    Class *superclass;

public:
    Class(string name, Class *superclass);
    Class(string name, string superclassName);
    Class(string name);

    string getName();

    Class *getSuperclass();
    void setSuperclass(Class *superclass);

    bool isChild(Class *_class);

    IObject *newInstance();
    IObject *newInstance(Tuple *args);

    bool hasMethod(string name);
    Method *getMethod(string name);
    void setMethod(Method *method);
    void setMethod(string name, Method *method);

    IObject *lookup(string name);

    IObject *call(string name, Tuple *args);

    string toString();

protected:
    virtual IObject *createNewInstance();
};
