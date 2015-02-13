#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Method;

class Class : public Object {
    string name;
    Class *superclass;

    map<string, Method *> methods;

public:
    Class(string name, Class *superclass);
    Class(string name, string superclassName);
    Class(string name);

    string getName();

    Class *getSuperclass();
    void setSuperclass(Class *superclass);

    bool isChild(Class *_class);

    virtual Object *newInstance();

    bool hasMethod(string name);
    Method *getMethod(string name);
    void setMethod(Method *method);

    Method *lookup(string name);

    Object *call(string name, Tuple *args);
    Object *call(string name, Object *arg);
    Object *call(string name);

    string toString();

    virtual void setupMethods();
};
}
