#pragma once
#include "common.h"

#include "class.h"

class RootClass : public Class {
public:
    RootClass(string name, Class *superclass);
    RootClass(string name, string superclassName);
    RootClass(string name);

    void setMethod(string name, function<Object *(Object *, Tuple *)> body);

    virtual void setupMethods() = 0;
};
