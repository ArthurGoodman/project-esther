#include "objectclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "tuple.h"
#include "io.h"
#include "signature.h"
#include "string.h"

ObjectClass::ObjectClass()
    : RootClass("Object", 0) {
}

void ObjectClass::setupMethods() {
    auto classMethod = [](Object *self, Tuple *) -> Object *{
        return self->getClass();
    };

    setMethod("class", new Signature, classMethod);

    auto printMethod = [](Object *self, Tuple *args) -> Object *{
        if (args->isEmpty())
            IO::print(self->toString());
        else
            foreach (i, (*args))
                IO::print((*i)->toString());

        return Runtime::getNull();
    };

    setMethod("print", new Signature("Object", {}, true), printMethod);

    auto scanMethod = [](Object *, Tuple *) -> Object *{
        return new String(IO::scan());
    };

    setMethod("scan", new Signature("String", {}), scanMethod);

    auto scanLineMethod = [](Object *, Tuple *) -> Object *{
        return new String(IO::scanLine());
    };

    setMethod("scanLine", new Signature("String", {}), scanLineMethod);

    auto equalsMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(self == args->at(0));
    };

    setMethod("equals", new Signature("Boolean", {"Object"}), equalsMethod);

    auto equalsOperator = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(self->equals(args->at(0)));
    };

    setMethod("==", new Signature("Boolean", {"Object"}), equalsOperator);

    auto notEqualsOperator = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(!self->equals(args->at(0)));
    };

    setMethod("!=", new Signature("Boolean", {"Object"}), notEqualsOperator);

    auto isMethod = [](Object *self, Tuple *args) -> Object *{
        return Runtime::toBoolean(self->is((Class *)args->at(0)));
    };

    setMethod("is", new Signature("Boolean", {"Class"}), isMethod);

    auto asMethod = [](Object *self, Tuple *args) -> Object *{
        return self->as((Class *)args->at(0));
    };

    setMethod("as", new Signature("Object", {"Class"}), asMethod);
}

Object *ObjectClass::createNewInstance() {
    return new Object;
}
