#include "objectclass.h"

#include "io.h"
#include "runtime.h"
#include "valueobject.h"
#include "stringclass.h"

Object *ObjectClass::createObject(Class *objectClass) {
    return new Object(objectClass);
}

Object *ObjectClass::createNewInstance(const std::vector<Object *> &) {
    return createObject(runtime->getObjectClass());
}

void ObjectClass::setupMethods() {
    defFunc("class", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    defFunc("==", { this }, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(self->call("equals", args)->isTrue());
    });

    defFunc("!=", { this }, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(!self->call("equals", args)->isTrue());
    });

    defFunc("toString", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return runtime->createString(self->toString());
    });

    defFunc("equals", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(self == args[0]);
    });

    defFunc("is", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<Class *>(args[0])) {
            Runtime::runtimeError(getName() + ".is: invalid argument");
            return nullptr;
        }

        return runtime->toBoolean(self->is((Class *)args[0]));
    });
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
