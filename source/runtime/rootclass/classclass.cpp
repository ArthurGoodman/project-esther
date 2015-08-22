#include "classclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "string.h"
#include "signature.h"
#include "tuple.h"

ClassClass::ClassClass()
    : RootClass("Class") {
    Runtime::getRootClass("Object")->setClass(this);
    setClass(this);
}

void ClassClass::setupMethods() {
    auto newMethod = [](Object * self, Tuple * args) -> Object * {
        return ((Class *)self)->newInstance(args);
    };

    setMethod("new", new Signature("Object", {}, true), newMethod);

    auto superclassMethod = [](Object * self, Tuple *) -> Object * {
        return ((Class *)self)->getSuperclass();
    };

    setMethod("superclass", new Signature("Class", {}), superclassMethod);

    auto nameMethod = [](Object * self, Tuple *) -> Object * {
        return new String(((Class *)self)->getName());
    };

    setMethod("name", new Signature("String", {}), nameMethod);

    auto isChildMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(((Class *)self)->isChild((Class *)args->at(0)));
    };

    setMethod("isChild", new Signature("Boolean", {"Class"}), isChildMethod);
}

Object *ClassClass::createNewInstance() {
    return new Class("");
}
