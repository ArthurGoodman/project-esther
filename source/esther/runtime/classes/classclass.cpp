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
    auto nameMethod = [](Object * self, Tuple *) -> Object * {
        return new String(((Class *)self)->getName());
    };

    setMethod(new Method("name", Runtime::getRoot(), {}, new NativeMethod(nameMethod)));
}
}
