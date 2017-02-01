#include "integerclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "nativefunction.h"

IntegerClass::IntegerClass(Esther *esther)
    : RootClass(esther, "Integer", esther->getRootClass("Numeric")) {
}

void IntegerClass::setupMethods(Esther *esther) {
    Pointer<IntegerClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                            if (!dynamic_cast<IntegerClass *>(*self)) {
                                Esther::runtimeError("Integer.(): invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[1])) {
                                Esther::runtimeError("Integer.(): invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, ((ValueObject *)*args[1])->getVariant().toInteger());
                        }));

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Integer.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());

        return self;
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());
        return self;
    });
}

Pointer<Object> IntegerClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new ValueObject(esther, 0);
}
