#include "rootclass.h"

#include "runtime.h"
#include "function.h"
#include "classclass.h"

RootClass::RootClass(Runtime *runtime, const std::string &name, Class *superclass)
    : Class(runtime->getClassClass(), name, superclass), runtime(runtime) {
    runtime->registerRootClass(this);
}

void RootClass::def(const std::string &name, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    def(name, std::list<Class *>(), body);
}

void RootClass::def(const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    std::list<Class *> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << runtime->getRootClass(name);

    def(name, paramsClasses, body);
}

void RootClass::def(const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    setAttribute(name, runtime->createNativeFunction(name, paramsClasses.size(), [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!self->getClass()->isChild(this)) {
            Runtime::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        int i = 0;
        for (Class *_class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Runtime::runtimeError(getName() + "." + name + ": invalid argument");
                return nullptr;
            }

        return body(self, args);
    }));
}
