#include "objectclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "tuple.h"
#include "io.h"
#include "signature.h"

ObjectClass::ObjectClass()
    : RootClass("Object", 0) {
}

Object *ObjectClass::newInstance() {
    return new Object;
}

void ObjectClass::setupMethods() {
    auto classMethod = [](Object * self, Tuple *) -> Object * {
        return self->getClass();
    };

    setMethod("class", new Signature, classMethod);

    auto printMethod = [](Object * self, Tuple * args) -> Object * {
        if (args->isEmpty())
            IO::print(self->toString());
        else
            foreach (i, (*args))
                IO::print((*i)->toString());

        return Runtime::getNull();
    };

    setMethod("print", new Signature("Object", {}), printMethod);

    auto equalsMethod = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(self == args->at(0));
    };

    setMethod("equals", new Signature("Boolean", {"Object"}), equalsMethod);

    auto equalsOperator = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(self->equals(args->at(0)));
    };

    setMethod("==", new Signature("Boolean", {"Object"}), equalsOperator);

    auto notEqualsOperator = [](Object * self, Tuple * args) -> Object * {
        return Runtime::toBoolean(!self->equals(args->at(0)));
    };

    setMethod("!=", new Signature("Boolean", {"Object"}), notEqualsOperator);
}
