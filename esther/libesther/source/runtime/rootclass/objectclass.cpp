#include "objectclass.h"

#include "io.h"
#include "runtime.h"

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
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
