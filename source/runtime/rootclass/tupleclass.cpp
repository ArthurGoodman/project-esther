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
    auto initMethod = [](IObject *self, Tuple *) -> IObject * {
        ((Tuple *)self)->initialize({});
        return self;
    };

    setMethod("initialize", new Signature("Object", {}), initMethod);

    auto initObjectMethod = [](IObject *self, Tuple *args) -> IObject * {
        ((Tuple *)self)->initialize({args->at(0)});
        return self;
    };

    setMethod("initialize", new Signature("Object", {"Object"}), initObjectMethod);

    auto sizeMethod = [](IObject *self, Tuple *) -> IObject * {
        return new Integer(((Tuple *)self)->size());
    };

    setMethod("size", new Signature("Integer", {}), sizeMethod);

    auto atMethod = [](IObject *self, Tuple *args) -> IObject * {
        return ((Tuple *)self)->at(((Integer *)args->at(0))->getVariant().toInteger());
    };

    setMethod("at", new Signature("Object", {"Integer"}), atMethod);
    setAttribute("[]", getMethod("at"));

    auto eachMethod = [](IObject *self, Tuple *args) -> IObject * {
        for(int i = 0; i < ((Tuple *)self)->size(); i++)
            ((Function *)args->at(0))->invoke(self, new Tuple({((Tuple *)self)->at(i)}));
        return Runtime::getNull();
    };

    setMethod("each", new Signature("Object", {"Function"}), eachMethod);
}

IObject *TupleClass::createNewInstance() {
    return new Tuple;
}
