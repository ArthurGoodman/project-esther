#include "rootclass.h"

#include "esther.h"
#include "function.h"
#include "classclass.h"
#include "valueobject.h"
#include "utility.h"

RootClass::RootClass(Esther *esther, const std::string &name, Pointer<Class> superclass)
    : Class(*esther->getClassClass(), name, superclass) {
    esther->registerRootClass(this);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    defFunc(esther, name, std::list<Pointer<Class>>(), body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    std::list<Pointer<Class>> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << esther->getRootClass(name);

    defFunc(esther, name, paramsClasses, body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<Pointer<Class>> &paramsClasses, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    std::string className = getName();

    defFunc(esther, name, paramsClasses.size(), [paramsClasses, name, body, className](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        int i = 0;
        for (Class *_class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Esther::runtimeError(className + "." + name + ": invalid argument");
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    std::string className = getName();

    defFunc(esther, name, arity, [name, body, className](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        for (int i = 0; i < (int)args.size(); i++)
            if (!dynamic_cast<ValueObject *>(*args[i])) {
                Esther::runtimeError(className + "." + name + ": invalid argument #" + Utility::toString(i));
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defFunc(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    std::string className = getName();
    Pointer<RootClass> _this = this;

    setAttribute(name, *esther->createNativeFunction(name, arity, [name, body, className, _this](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!self->getClass()->isChild(*_this)) {
            Esther::runtimeError(className + "." + name + ": invalid self");
            return nullptr;
        }

        return body(esther, self, args);
    }));
}

void RootClass::defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &)) {
    std::string className = getName();

    setAttribute(name, *esther->createNativeFunction(name, 1, [name, body, className](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!dynamic_cast<ValueObject *>(*self)) {
            Esther::runtimeError(className + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(*args[0])) {
            Esther::runtimeError(className + "." + name + ": invalid argument");
            return nullptr;
        }

        return *esther->createValueObject(body(((ValueObject *)*self)->getVariant(), ((ValueObject *)*args[0])->getVariant()));
    }));
}

void RootClass::defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &)) {
    std::string className = getName();

    setAttribute(name, *esther->createNativeFunction(name, 1, [name, body, className](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        if (!dynamic_cast<ValueObject *>(*self)) {
            Esther::runtimeError(className + "." + name + ": invalid self");
            return nullptr;
        }

        if (!dynamic_cast<ValueObject *>(*args[0])) {
            Esther::runtimeError(className + "." + name + ": invalid argument");
            return nullptr;
        }

        return esther->toBoolean(body(((ValueObject *)*self)->getVariant(), ((ValueObject *)*args[0])->getVariant()));
    }));
}
