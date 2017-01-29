#include "objectclass.h"

#include "io.h"
#include "esther.h"
#include "valueobject.h"
#include "stringclass.h"

Object *ObjectClass::createObject(Class *objectClass) {
    return new Object(objectClass);
}

Object *ObjectClass::createNewInstance(const std::vector<Object *> &) {
    return createObject(this);
}

void ObjectClass::setupMethods(Esther *esther) {
    defFunc(esther, "class", [=](Esther *, Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    defFunc(esther, "==", { this }, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "!=", { this }, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(!self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "toString", [=](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return esther->createString(self->toString());
    });

    defFunc(esther, "equals", 1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self == args[0]);
    });

    defFunc(esther, "is", 1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<Class *>(args[0])) {
            Esther::runtimeError(getName() + ".is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is((Class *)args[0]));
    });
}

ObjectClass::ObjectClass(Esther *esther)
    : RootClass(esther, "Object", nullptr) {
}
