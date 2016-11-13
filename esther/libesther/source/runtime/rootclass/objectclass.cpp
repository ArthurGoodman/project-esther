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
    def("write", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!args.empty())
            for (Object *arg : args)
                IO::write(arg->call("toString", {}, runtime->getStringClass())->toString());
        else
            IO::write(self->call("toString", {}, runtime->getStringClass())->toString());

        return runtime->getNull();
    });

    def("writeLine", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!args.empty())
            for (Object *arg : args)
                IO::writeLine(arg->call("toString", {}, runtime->getStringClass())->toString());
        else
            IO::writeLine(self->call("toString", {}, runtime->getStringClass())->toString());

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

    def("equals", 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return runtime->toBoolean(self == args[0]);
    });
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
