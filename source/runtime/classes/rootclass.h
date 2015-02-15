#pragma once
#include "common.h"

#include "class.h"

class RootClass : public Class {
public:
    RootClass(string name, Class *superclass);
    RootClass(string name, string superclassName);
    RootClass(string name);

    virtual void setupMethods() = 0;
};
