#include "runtime/rootclass/rootclass.h"

#include "common/utility.h"
#include "esther.h"
#include "runtime/nativefunction.h"
#include "runtime/rootclass/classclass.h"
#include "runtime/valueobject.h"

namespace es {

RootClass::RootClass(Esther *esther, const std::string &name, Class *volatile superclass)
    : Class(esther, name, superclass) {
    esther->registerRootClass(this);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body) {
    defFunc(esther, name, std::list<Class *>(), body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body) {
    std::list<Class *> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << esther->getRootClass(name);

    defFunc(esther, name, paramsClasses, body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body) {
    defFunc(esther, name, paramsClasses.size(), [=](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
        size_t i = 0;
        for (Class *volatile _class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Esther::runtimeError("%s.%s: invalid argument", getName().c_str(), name.c_str());
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body) {
    defFunc(esther, name, arity, [=](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
        for (size_t i = 0; i < args.size(); i++)
            if (!dynamic_cast<ValueObject *volatile>(args[i])) {
                Esther::runtimeError("%s.%s: invalid argument #%i", getName().c_str(), name.c_str(), i);
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body) {
    setAttribute(name, new NativeFunction(esther, name, arity, [=](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
                     if (!self->getClass()->isChild(this)) {
                         Esther::runtimeError("%s.%s: invalid self", getName().c_str(), name.c_str());
                         return nullptr;
                     }

                     return body(esther, self, args);
                 }));
}

void RootClass::defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &)) {
    setAttribute(name, new NativeFunction(esther, name, 1, [=](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
                     if (!dynamic_cast<ValueObject *volatile>(self)) {
                         Esther::runtimeError("%s.%s: invalid self", getName().c_str(), name.c_str());
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *volatile>(args[0])) {
                         Esther::runtimeError("%s.%s: invalid argument", getName().c_str(), name.c_str());
                         return nullptr;
                     }

                     return new ValueObject(esther, body(static_cast<ValueObject *volatile>(self)->getVariant(), static_cast<ValueObject *volatile>(args[0])->getVariant()));
                 }));
}

void RootClass::defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &)) {
    setAttribute(name, new NativeFunction(esther, name, 1, [=](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
                     if (!dynamic_cast<ValueObject *volatile>(self)) {
                         Esther::runtimeError("%s.%s: invalid self", getName().c_str(), name.c_str());
                         return nullptr;
                     }

                     if (!dynamic_cast<ValueObject *volatile>(args[0])) {
                         Esther::runtimeError("%s.%s: invalid argument", getName().c_str(), name.c_str());
                         return nullptr;
                     }

                     return esther->toBoolean(body(static_cast<ValueObject *volatile>(self)->getVariant(), static_cast<ValueObject *volatile>(args[0])->getVariant()));
                 }));
}
}
