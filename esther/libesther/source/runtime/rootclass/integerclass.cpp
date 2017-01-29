#include "integerclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "function.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance(const std::vector<Object *> &) {
    return createInteger(0);
}

void IntegerClass::setupMethods(Esther *esther) {
    setAttribute("()", esther->createNativeFunction("()", 2, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<IntegerClass *>(self)) {
            Esther::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Esther::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return esther->createInteger(((ValueObject *)args[1])->getVariant().toInteger());
    }));

    defValueObjectFunc(esther, "initialize", -1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toInteger());

        return self;
    });

    defValueObjectFunc(esther, "=", 1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toInteger());
        return self;
    });
}

IntegerClass::IntegerClass(Esther *esther)
    : RootClass(esther, "Integer", esther->getNumericClass()) {
}
