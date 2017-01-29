#include "floatclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "function.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance(const std::vector<Object *> &) {
    return createFloat(0.0);
}

void FloatClass::setupMethods(Esther *esther) {
    setAttribute("()", esther->createNativeFunction("()", 2, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<FloatClass *>(self)) {
            Esther::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Esther::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return esther->createFloat(((ValueObject *)args[1])->getVariant().toReal());
    }));

    defValueObjectFunc(esther, "initialize", -1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Esther::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toReal());

        return self;
    });

    defValueObjectFunc(esther, "=", 1, [=](Esther *, Object *self, const std::vector<Object *> &args) -> Object * {
        ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toReal());
        return self;
    });
}

FloatClass::FloatClass(Esther *esther)
    : RootClass(esther, "Float", esther->getNumericClass()) {
}
