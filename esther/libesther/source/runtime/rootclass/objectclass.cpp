#include "objectclass.h"

#include "io.h"
#include "esther.h"
#include "valueobject.h"
#include "stringclass.h"

Pointer<Object> ObjectClass::createObject(Pointer<Class> objectClass) {
    return new Object(objectClass);
}

Pointer<Object> ObjectClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    return createObject(this);
}

void ObjectClass::setupMethods(Esther *esther) {
    defFunc(esther, "class", [](Esther *, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return *self->getClass();
    });

    defFunc(esther, "==", { this }, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "!=", { this }, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(!self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "toString", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return *esther->createString(self->toString());
    });

    defFunc(esther, "equals", 1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return esther->toBoolean(self == args[0]);
    });

    defFunc(esther, "is", 1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!dynamic_cast<Class *>(*args[0])) {
            Esther::runtimeError("Object.is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is((Class *)*args[0]));
    });
}

ObjectClass::ObjectClass(Esther *esther)
    : RootClass(esther, "Object", nullptr) {
}
