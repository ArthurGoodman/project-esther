#include "tupleclass.h"

#include "runtime.h"
#include "tuple.h"
#include "integer.h"

TupleClass::TupleClass()
    : Class("Tuple") {
    Runtime::setRootClass(this);
}

Object *TupleClass::newInstance() {
    return new Tuple;
}

void TupleClass::setupMethods() {
    auto sizeMethod = [](Object * self, Tuple *) -> Object * {
        return new Integer(((Tuple *)self)->size());
    };

    setMethod("size", sizeMethod);

    auto atMethod = [](Object * self, Tuple * args) -> Object * {
        return ((Tuple *)self)->at(((Integer *)args->at(0))->getVariant().toInteger());
    };

    setMethod("at", atMethod);
}
