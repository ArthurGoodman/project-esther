#include "objectclass.h"

#include "io.h"
#include "runtime.h"

Object *ObjectClass::createObject(Class *objectClass) {
    return new Object(objectClass);
}

Object *ObjectClass::createNewInstance(const std::vector<Object *> &) {
    return createObject(runtime->getObjectClass());
}

void ObjectClass::setupMethods() {
    def("write", {this}, [=](Object *, const std::vector<Object *> &args) -> Object * {
        IO::print(args[0]->toString());
        return runtime->getNull();
    });

    def("writeLine", {this}, [=](Object *, const std::vector<Object *> &args) -> Object * {
        IO::printLine(args[0]->toString());
        return runtime->getNull();
    });

    def("class", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return self->getClass();
    });

    def("==", {this}, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return self->call("equals", args);
    });
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
