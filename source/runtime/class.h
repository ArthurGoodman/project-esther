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

    Object *newInstance();
    Object *newInstance(Tuple *args);

    bool hasMethod(string name);
    Method *getMethod(string name);
    void setMethod(Method *method);
    void setMethod(string name, Method *method);

    Object *lookup(string name);

    Object *call(string name, Tuple *args);
    Object *call(string name, Object *arg);
    Object *call(string name);

    string immediateToString();

protected:
    virtual Object *createNewInstance();
};
