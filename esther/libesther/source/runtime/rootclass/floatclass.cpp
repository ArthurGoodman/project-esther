#include "floatclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "numericclass.h"
#include "function.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance(const std::vector<Object *> &) {
    return createFloat(0.0);
}

void FloatClass::setupMethods() {
    setAttribute("()", runtime->createNativeFunction("()", 2, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<FloatClass *>(self)) {
            Runtime::runtimeError(getName() + ".(): invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[1])) {
            Runtime::runtimeError(getName() + ".(): invalid argument");
            return nullptr;
        }

        return runtime->createFloat(((ValueObject *)args[1])->getVariant().toReal());
    }));

    def("initialize", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if ((int)args.size() > 1)
            Runtime::runtimeError(getName() + ".initialize: invalid number of arguments");

        if (!args.empty()) {
            if (!dynamic_cast<ValueObject *>(args[0])) {
                Runtime::runtimeError(getName() + ".initialize: invalid argument");
                return nullptr;
            }

            ((ValueObject *)self)->setVariant(((ValueObject *)args[0])->getVariant().toReal());
        }

        return self;
    });
}

FloatClass::FloatClass(Runtime *runtime)
    : RootClass(runtime, "Float", runtime->getNumericClass()) {
}
