#include "integerclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "function.h"

Pointer<ValueObject> IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Pointer<Object> IntegerClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    return *createInteger(0);
}

void IntegerClass::setupMethods(Esther *esther) {
    setAttribute("()", *esther->createNativeFunction("()", 2, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!dynamic_cast<IntegerClass *>(*self)) {
            Esther::runtimeError("Integer.(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(*args[1])) {
            Esther::runtimeError("Integer.(): invalid argument");
            return nullptr;
        }

        return *esther->createInteger(((ValueObject *)*args[1])->getVariant().toInteger());
    }));

    defValueObjectFunc(esther, "initialize", -1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Integer.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());

        return self;
    });

    defValueObjectFunc(esther, "=", 1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());
        return self;
    });
}

IntegerClass::IntegerClass(Esther *esther)
    : RootClass(esther, "Integer", *esther->getNumericClass()) {
}
