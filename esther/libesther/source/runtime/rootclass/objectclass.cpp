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
    def("write", {this}, [=](Object *, const std::vector<Object *> &args) -> Object * {
        IO::write(args[0]->call("toString", {}, runtime->getStringClass())->toString());
        return runtime->getNull();
    });

    def("writeLine", {this}, [=](Object *, const std::vector<Object *> &args) -> Object * {
        IO::writeLine(args[0]->call("toString", {}, runtime->getStringClass())->toString());
        return runtime->getNull();
    });

    def("class", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    def("==", {this}, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(self->call("equals", args)->isTrue());
    });

    def("!=", {this}, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(!self->call("equals", args)->isTrue());
    });

    def("toString", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return runtime->createString(self->toString());
    });
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
