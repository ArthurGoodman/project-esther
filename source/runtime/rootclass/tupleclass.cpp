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
    auto initMethod = [](Object *self, Tuple *) -> Object * {
        ((Tuple *)self)->initialize({});
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initObjectMethod = [](Object *self, Tuple *args) -> Object * {
        ((Tuple *)self)->initialize({args->at(0)});
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Object"}), initObjectMethod);

    auto sizeMethod = [](Object *self, Tuple *) -> Object * {
        return new Integer(((Tuple *)self)->size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](Object *self, Tuple *args) -> Object * {
        return ((Tuple *)self)->at(((Integer *)args->at(0))->getVariant().toInteger());
    };

    setMethod("at", new Signature("Object", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));

    auto eachMethod = [](Object *self, Tuple *args) -> Object * {
        for(int i = 0; i < ((Tuple *)self)->size(); i++)
            ((Function *)args->at(0))->invoke(self, new Tuple({((Tuple *)self)->at(i)}));
        return Runtime::getNull();
    };

    setMethod("each", new Signature("Object", {"Function"}), eachMethod);
}

Object *TupleClass::createNewInstance() {
    return new Tuple;
}
