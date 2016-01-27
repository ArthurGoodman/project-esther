#include "contextclass.h"

#include "runtime.h"
#include "context.h"
#include "signature.h"
#include "tuple.h"
#include "string.h"

ContextClass::ContextClass()
    : RootClass("Context") {
}

void ContextClass::setupMethods() {
    auto parentMethod = [](Object *self, Tuple *) -> Object * {
        return ((Context *)self)->getParent();
    };

    setMethod("parent", new Signature("Context", {}), parentMethod);

    auto hasLocalMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((Context *)self)->hasLocal(((String *)args->at(0))->callToString()));
    };

    setMethod("hasLocal", new Signature("Boolean", {"String"}), hasLocalMethod);

    auto getLocalMethod = [](Object *self, Tuple *args) -> Object * {
        return ((Context *)self)->getLocal(((String *)args->at(0))->callToString());
    };

    setMethod("getLocal", new Signature("Object", {"String"}), getLocalMethod);

    auto setLocalMethod = [](Object *self, Tuple *args) -> Object * {
        ((Context *)self)->setLocal(((String *)args->at(0))->callToString(), args->at(1));
        return args->at(1);
    };

    setMethod("setLocal", new Signature("Object", {"String", "Object"}), setLocalMethod);

    auto hasMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((Context *)self)->hasId(((String *)args->at(0))->callToString()));
    };

    setMethod("has", new Signature("Boolean", {"String"}), hasMethod);

    auto getMethod = [](Object *self, Tuple *args) -> Object * {
        return ((Context *)self)->getId(((String *)args->at(0))->callToString());
    };

    setMethod("get", new Signature("Object", {"String"}), getMethod);

    auto _setMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(((Context *)self)->setId(((String *)args->at(0))->callToString(), args->at(1)));
    };

    setMethod("set", new Signature("Object", {"String", "Object"}), _setMethod);
}

Object *ContextClass::createNewInstance() {
    return new Context;
}
