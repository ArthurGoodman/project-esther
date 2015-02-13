#include "objectclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "tuple.h"
#include "io.h"

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

    setMethod("class", classMethod);

    auto printMethod = [](Object * self, Tuple * args) -> Object * {
        if (args->isEmpty())
            IO::print(self->toString());
        else
            foreach (i, (*args))
                IO::print((*i)->toString());

        return Runtime::getNull();
    };

    setMethod("print", printMethod);
}
}
