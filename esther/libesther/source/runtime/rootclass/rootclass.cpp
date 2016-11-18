#include "rootclass.h"

#include "runtime.h"
#include "function.h"
#include "classclass.h"
#include "valueobject.h"
#include "utility.h"

RootClass::RootClass(Runtime *runtime, const std::string &name, Class *superclass)
    : Class(runtime->getClassClass(), name, superclass), runtime(runtime) {
    runtime->registerRootClass(this);
}

void RootClass::defFunc(const std::string &name, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, std::list<Class *>(), body);
}

void RootClass::defFunc(const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    std::list<Class *> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << runtime->getRootClass(name);

    defFunc(name, paramsClasses, body);
}

void RootClass::defFunc(const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, paramsClasses.size(), [=](Object *self, const std::vector<Object *> &args) -> Object * {
        int i = 0;
        for (Class *_class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Runtime::runtimeError(getName() + "." + name + ": invalid argument");
                return nullptr;
            }

        return body(self, args);
    });
}

void RootClass::defValueObjectFunc(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, arity, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        for (int i = 0; i < (int)args.size(); i++)
            if (!dynamic_cast<ValueObject *>(args[i])) {
                Runtime::runtimeError(getName() + "." + name + ": invalid argument #" + Utility::toString(i));
                return nullptr;
            }

        return body(self, args);
    });
}

void RootClass::defFunc(const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body) {
    setAttribute(name, runtime->createNativeFunction(name, arity, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!self->getClass()->isChild(this)) {
            Runtime::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        return body(self, args);
    }));
}

void RootClass::defOper(const std::string &name, Variant (*body)(const Variant &, const Variant &)) {
    setAttribute(name, runtime->createNativeFunction(name, 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<ValueObject *>(self)) {
            Runtime::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[0])) {
            Runtime::runtimeError(getName() + "." + name + ": invalid argument");
            return nullptr;
        }

        return runtime->createValueObject(body(((ValueObject *)self)->getVariant(), ((ValueObject *)args[0])->getVariant()));
    }));
}

void RootClass::defPred(const std::string &name, bool (*body)(const Variant &, const Variant &)) {
    setAttribute(name, runtime->createNativeFunction(name, 1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<ValueObject *>(self)) {
            Runtime::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[0])) {
            Runtime::runtimeError(getName() + "." + name + ": invalid argument");
            return nullptr;
        }

        return runtime->toBoolean(body(((ValueObject *)self)->getVariant(), ((ValueObject *)args[0])->getVariant()));
    }));
}
