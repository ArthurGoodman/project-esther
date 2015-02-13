#include "objectclass.h"

#include "runtime.h"
#include "tuple.h"
#include "io.h"
#include "nativemethod.h"
#include "method.h"

namespace esther {

ObjectClass::ObjectClass()
    : Class("Object", 0) {
    Runtime::setRootClass(this);
}

Object *ObjectClass::newInstance() {
    return new Object;
}

void ObjectClass::setupMethods() {
    auto classMethod = [](Object * self, Tuple *) -> Object * {
        return self->getClass();
    };

    setMethod(new Method("class", Runtime::getRoot(), {}, new NativeMethod(classMethod)));

    auto printMethod = [](Object * self, Tuple * args) -> Object * {
        if (args->isEmpty())
            IO::print(self->toString());
        else
            foreach (i, (*args))
                IO::print((*i)->toString());

        return Runtime::getNull();
    };
    setMethod(new Method("print", Runtime::getRoot(), {}, new NativeMethod(printMethod)));
}
}
