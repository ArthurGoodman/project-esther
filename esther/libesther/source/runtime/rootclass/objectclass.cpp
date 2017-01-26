#include "objectclass.h"

#include "io.h"
#include "esther.h"
#include "valueobject.h"
#include "stringclass.h"

Object *ObjectClass::createObject(Class *objectClass) {
    return new Object(objectClass);
}

Object *ObjectClass::createNewInstance(const std::vector<Object *> &) {
    return createObject(esther->getObjectClass());
}

void ObjectClass::setupMethods() {
    defFunc("class", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    defFunc("==", { this }, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self->call("equals", args)->isTrue());
    });

    defFunc("!=", { this }, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(!self->call("equals", args)->isTrue());
    });

    defFunc("toString", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return esther->createString(self->toString());
    });

    defFunc("equals", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self == args[0]);
    });

    defFunc("is", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<Class *>(args[0])) {
            Esther::runtimeError(getName() + ".is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is((Class *)args[0]));
    });
}

ObjectClass::ObjectClass(Esther *e)
    : RootClass(e, "Object", nullptr) {
}
