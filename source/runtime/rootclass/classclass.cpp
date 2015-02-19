#include "classclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "string.h"
#include "signature.h"

ClassClass::ClassClass()
    : RootClass("Class") {
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

    setMethod("new", new Signature("Object", {}), newMethod);

    auto superclassMethod = [](Object * self, Tuple *) -> Object * {
        return ((Class *)self)->getSuperclass();
    };

    setMethod("superclass", new Signature("Class", {}), superclassMethod);

    auto nameMethod = [](Object * self, Tuple *) -> Object * {
        return new String(((Class *)self)->getName());
    };

    setMethod("name", new Signature("String", {}), nameMethod);
}
