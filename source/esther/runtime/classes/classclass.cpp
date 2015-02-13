#include "classclass.h"

#include "runtime.h"
#include "method.h"
#include "nativemethod.h"
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

    setMethod(new Method("new", Runtime::getRoot(), {}, new NativeMethod(newMethod)));

    auto superclassMethod = [](Object * self, Tuple *) -> Object * {
        return ((Class *)self)->getSuperclass();
    };

    setMethod(new Method("superclass", Runtime::getRoot(), {}, new NativeMethod(superclassMethod)));

    auto nameMethod = [](Object * self, Tuple *) -> Object * {
        return new String(((Class *)self)->getName());
    };

    setMethod(new Method("name", Runtime::getRoot(), {}, new NativeMethod(nameMethod)));
}
}
