#include "tupleclass.h"

#include "runtime.h"
#include "tuple.h"
#include "integer.h"
#include "signature.h"
#include "method.h"

TupleClass::TupleClass()
    : RootClass("Tuple") {
}

void TupleClass::setupMethods() {
    auto sizeMethod = [](Object *self, Tuple *) -> Object *{
        return new Integer(((Tuple *)self)->size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](Object *self, Tuple *args) -> Object *{
        return ((Tuple *)self)->at(((Integer *)args->at(0))->getVariant().toInteger());
    };

    setMethod("at", new Signature("Object", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));
}

Object *TupleClass::createNewInstance() {
    return new Tuple;
}
