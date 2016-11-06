#include "rootclass.h"

#include "runtime.h"
#include "function.h"

RootClass::RootClass(Runtime *runtime, Class *objectClass, const std::string &name, Class *superclass)
    : Class(objectClass, name, superclass), runtime(runtime) {
}

void RootClass::def(const std::string &name, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    setAttribute(name, runtime->createNativeFunction(name, 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (self->getClass() != this) {
            Runtime::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        if (args[0]->getClass() != this) {
            Runtime::runtimeError(getName() + "." + name + ": invalid argument");
            return nullptr;
        }

        return body(self, args);
    }));
}
