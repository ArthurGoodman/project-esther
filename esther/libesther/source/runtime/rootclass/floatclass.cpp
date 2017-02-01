#include "floatclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "nativefunction.h"

FloatClass::FloatClass(Esther *esther)
    : RootClass(esther, "Float", esther->getRootClass("Numeric")) {
}

void FloatClass::setupMethods(Esther *esther) {
    Pointer<FloatClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                            if (!dynamic_cast<FloatClass *>(*self)) {
                                Esther::runtimeError("Float.(): invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[1])) {
                                Esther::runtimeError("Float.(): invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, ((ValueObject *)*args[1])->getVariant().toReal());
                        }));

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Float.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toReal());

        return self;
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toReal());
        return self;
    });
}

void FloatClass::copy(ManagedObject *dst) {
    new (dst) FloatClass(*this);
}

Pointer<Object> FloatClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new ValueObject(esther, 0.0);
}
