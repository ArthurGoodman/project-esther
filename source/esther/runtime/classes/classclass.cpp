#include "classclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "string.h"

namespace esther {

ClassClass::ClassClass()
    : Class("Class") {
    Runtime::setRootClass(this);

    Runtime::getRootClass("Object")->setClass(this);
    setClass(this);
}

Object *ClassClass::newInstance() {
    return new Class("");
}

void ClassClass::setupMethods() {
    auto newMethod = [](Object * self, Tuple *) -> Object * {
        return ((Class *)self)->newInstance();
    };

    setMethod("new", newMethod);

    auto superclassMethod = [](Object * self, Tuple *) -> Object * {
        return ((Class *)self)->getSuperclass();
    };

    setMethod("superclass", superclassMethod);

    auto nameMethod = [](Object * self, Tuple *) -> Object * {
        return new String(((Class *)self)->getName());
    };

    setMethod("name", nameMethod);
}
}
