#include "rootclass.h"

#include "runtime.h"

RootClass::RootClass(string name, Class *superclass)
    : Class(name, superclass) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(string name, string superclassName)
    : Class(name, superclassName) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(string name)
    : Class(name) {
    Runtime::setRootClass(this);
}
