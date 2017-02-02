#include "objectclass.h"

#include "common/io.h"
#include "runtime/esther.h"
#include "runtime/valueobject.h"
#include "runtime/rootclass/stringclass.h"

ObjectClass::ObjectClass(Esther *esther)
    : RootClass(esther, "Object", nullptr) {
}

void ObjectClass::setupMethods(Esther *esther) {
    Ptr<ObjectClass> _this = this;

    _this->defFunc(esther, "class", [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return *self->getClass();
    });

    _this->defFunc(esther, "==", { this }, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        return esther->toBoolean(self->call(esther, "equals", args)->isTrue());
    });

    _this->defFunc(esther, "!=", { this }, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        return esther->toBoolean(!self->call(esther, "equals", args)->isTrue());
    });

    _this->defFunc(esther, "toString", [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return new ValueObject(esther, self->toString());
    });

    _this->defFunc(esther, "equals", 1, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        return esther->toBoolean(self == args[0]);
    });

    _this->defFunc(esther, "is", 1, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        if (!dynamic_cast<Class *>(*args[0])) {
            Esther::runtimeError("Object.is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is((Class *)*args[0]));
    });
}

Ptr<Object> ObjectClass::createNewInstance(Esther *, const std::vector<Ptr<Object>> &) {
    return new Object(this);
}
