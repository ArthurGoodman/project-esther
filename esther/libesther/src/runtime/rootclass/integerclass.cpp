#include "runtime/rootclass/integerclass.h"

#include "runtime/valueobject.h"
#include "esther.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/nativefunction.h"

namespace es {

IntegerClass::IntegerClass(Esther *esther)
    : RootClass(esther, "Integer", esther->getRootClass("Numeric")) {
}

void IntegerClass::setupMethods(Esther *esther) {
    setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
                     if (!dynamic_cast<IntegerClass *>(self)) {
                         Esther::runtimeError("Integer.(): invalid self");
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *>(args[1])) {
                         Esther::runtimeError("Integer.(): invalid argument");
                         return nullptr;
                     }

                     return new ValueObject(esther, static_cast<ValueObject *>(args[1])->getVariant().toInteger());
                 }));

    defValueObjectFunc(esther, "initialize", -1, [](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if (static_cast<int>(args.size()) > 1)
            Esther::runtimeError("Integer.initialize: invalid number of arguments");

        if (!args.empty())
            static_cast<ValueObject *>(self)->setVariant(static_cast<ValueObject *>(args[0])->getVariant().toInteger());

        return self;
    });

    defValueObjectFunc(esther, "=", 1, [](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        static_cast<ValueObject *>(self)->setVariant(static_cast<ValueObject *>(args[0])->getVariant().toInteger());
        return self;
    });
}

Object *IntegerClass::createNewInstance(Esther *esther, const std::vector<Object *> &) {
    return new ValueObject(esther, 0);
}
}
