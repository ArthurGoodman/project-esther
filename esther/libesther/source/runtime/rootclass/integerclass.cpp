#include "integerclass.h"

#include "valueobject.h"
#include "esther.h"
#include "numericclass.h"
#include "nativefunction.h"

IntegerClass::IntegerClass(Esther *esther)
    : RootClass(esther, "Integer", esther->getRootClass("Numeric")) {
}

void IntegerClass::setupMethods(Esther *esther) {
    Ptr<IntegerClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
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

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Integer.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());

        return self;
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toInteger());
        return self;
    });
}

Ptr<Object> IntegerClass::createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &) {
    return new ValueObject(esther, 0);
}
