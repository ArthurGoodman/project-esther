#include "runtime/rootclass/objectclass.h"

#include "common/io.h"
#include "esther.h"
#include "runtime/valueobject.h"
#include "runtime/rootclass/stringclass.h"

namespace es {

ObjectClass::ObjectClass(Esther *esther)
    : RootClass(esther, "Object", nullptr) {
}

void ObjectClass::setupMethods(Esther *esther) {
    defFunc(esther, "class", [](Esther *, Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    defFunc(esther, "==", { this }, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "!=", { this }, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(!self->call(esther, "equals", args)->isTrue());
    });

    defFunc(esther, "toString", [](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return new ValueObject(esther, self->toString());
    });

    defFunc(esther, "equals", 1, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return esther->toBoolean(self == args[0]);
    });

    defFunc(esther, "is", 1, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<Class *>(args[0])) {
            Esther::runtimeError("Object.is: invalid argument");
            return nullptr;
        }

        return esther->toBoolean(self->is(static_cast<Class *>(args[0])));
    });
}

Object *ObjectClass::createNewInstance(Esther *, const std::vector<Object *> &) {
    return new Object(this);
}
}
