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
    auto newMethod = [](IObject *self, Tuple *args) -> IObject * {
        return ((Class *)self)->newInstance(args);
    };

    setMethod("new", new Signature("Object", {}, true), newMethod);
    setAttribute("()", getMethod("new"));

    auto superclassMethod = [](IObject *self, Tuple *) -> IObject * {
        return ((Class *)self)->getSuperclass();
    };

    setMethod("superclass", new Signature("Class", {}), superclassMethod);

    auto nameMethod = [](IObject *self, Tuple *) -> IObject * {
        return new String(((Class *)self)->getName());
    };

    setMethod("name", new Signature("String", {}), nameMethod);

    auto isChildMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(((Class *)self)->isChild((Class *)args->at(0)));
    };

    setMethod("isChild", new Signature("Boolean", {"Class"}), isChildMethod);
}

IObject *ClassClass::createNewInstance() {
    return new Class("");
}
