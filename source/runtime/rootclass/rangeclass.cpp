#include "rangeclass.h"

#include "range.h"
#include "signature.h"
#include "tuple.h"
#include "integer.h"
#include "runtime.h"

RangeClass::RangeClass()
    : RootClass("Range") {
}

void RangeClass::setupMethods() {
    auto initMethod = [](Object *self, Tuple *args) -> Object * {
        ((Range *)self)->setFirst(((Integer *)args->at(0))->getVariant().toInteger());
        ((Range *)self)->setSecond(((Integer *)args->at(1))->getVariant().toInteger());
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Integer", "Integer"}), initMethod);

    auto eachMethod = [](Object *self, Tuple *args) -> Object * {
        ((Range *)self)->each((Function *)args->at(0));
        return Runtime::getNull();
    };

    setMethod("each", new Signature("Object", {"Function"}), eachMethod);
}

Object *RangeClass::createNewInstance() {
    return new Range(0, 0);
}
