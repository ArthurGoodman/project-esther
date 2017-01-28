#include "rootclass.h"

#include "esther.h"
#include "function.h"
#include "classclass.h"
#include "valueobject.h"
#include "utility.h"

RootClass::RootClass(Esther *esther, const std::string &name, Class *superclass)
    : Class(esther->getClassClass(), name, superclass)
    , esther(esther) {
    esther->registerRootClass(this);
}

void RootClass::defFunc(const std::string &name, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, std::list<Class *>(), body);
}

void RootClass::defFunc(const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    std::list<Class *> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << esther->getRootClass(name);

    defFunc(name, paramsClasses, body);
}

void RootClass::defFunc(const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, paramsClasses.size(), [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        int i = 0;
        for (Class *_class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Esther::runtimeError(getName() + "." + name + ": invalid argument");
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defValueObjectFunc(const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    defFunc(name, arity, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        for (int i = 0; i < (int)args.size(); i++)
            if (!dynamic_cast<ValueObject *>(args[i])) {
                Esther::runtimeError(getName() + "." + name + ": invalid argument #" + Utility::toString(i));
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defFunc(const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    setAttribute(name, esther->createNativeFunction(name, arity, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!self->getClass()->isChild(this)) {
            Esther::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        return body(esther, self, args);
    }));
}

void RootClass::defOper(const std::string &name, Variant (*body)(const Variant &, const Variant &)) {
    setAttribute(name, esther->createNativeFunction(name, 1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<ValueObject *>(self)) {
            Esther::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[0])) {
            Esther::runtimeError(getName() + "." + name + ": invalid argument");
            return nullptr;
        }

        return esther->createValueObject(body(((ValueObject *)self)->getVariant(), ((ValueObject *)args[0])->getVariant()));
    }));
}

void RootClass::defPred(const std::string &name, bool (*body)(const Variant &, const Variant &)) {
    setAttribute(name, esther->createNativeFunction(name, 1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        if (!dynamic_cast<ValueObject *>(self)) {
            Esther::runtimeError(getName() + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(args[0])) {
            Esther::runtimeError(getName() + "." + name + ": invalid argument");
            return nullptr;
        }

        return esther->toBoolean(body(((ValueObject *)self)->getVariant(), ((ValueObject *)args[0])->getVariant()));
    }));
}
