#include "objectclass.h"

#include "io.h"
#include "esther.h"
#include "valueobject.h"
#include "stringclass.h"

ObjectClass::ObjectClass(Esther *esther)
    : RootClass(esther, "Object", nullptr) {
}

void ObjectClass::setupMethods(Esther *esther) {
    Pointer<ObjectClass> _this = this;

    _this->defFunc(esther, "class", [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return *self->getClass();
    });

    _this->defFunc(esther, "==", { this }, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(self->call(esther, "equals", args)->isTrue());
    });

    _this->defFunc(esther, "!=", { this }, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(!self->call(esther, "equals", args)->isTrue());
    });

    _this->defFunc(esther, "toString", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return new ValueObject(esther, self->toString());
    });

    _this->defFunc(esther, "equals", 1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(self == args[0]);
    });

    _this->defFunc(esther, "is", 1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!dynamic_cast<Class *>(*args[0])) {
            Esther::runtimeError("Object.is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is((Class *)*args[0]));
    });
}

Pointer<Object> ObjectClass::createNewInstance(Esther *, const std::vector<Pointer<Object>> &) {
    return new Object(this);
}
