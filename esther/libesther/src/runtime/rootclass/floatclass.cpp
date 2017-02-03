#include "runtime/rootclass/floatclass.h"

#include "runtime/valueobject.h"
#include "esther.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/nativefunction.h"

namespace es {

FloatClass::FloatClass(Esther *esther)
    : RootClass(esther, "Float", esther->getRootClass("Numeric")) {
}

void FloatClass::setupMethods(Esther *esther) {
    Ptr<FloatClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
                            if (!dynamic_cast<FloatClass *>(*self)) {
                                Esther::runtimeError("Float.(): invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[1])) {
                                Esther::runtimeError("Float.(): invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, static_cast<ValueObject *>(*args[1])->getVariant().toReal());
                        }));

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        if (static_cast<int>(args.size()) > 1)
            Esther::runtimeError("Float.initialize: invalid number of arguments");

        if (!args.empty())
            static_cast<ValueObject *>(*self)->setVariant(static_cast<ValueObject *>(*args[0])->getVariant().toReal());

        return self;
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        static_cast<ValueObject *>(*self)->setVariant(static_cast<ValueObject *>(*args[0])->getVariant().toReal());
        return self;
    });
}

Ptr<Object> FloatClass::createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &) {
    return new ValueObject(esther, 0.0);
}
}
