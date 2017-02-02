#include "rootclass.h"

#include "runtime/esther.h"
#include "runtime/nativefunction.h"
#include "runtime/rootclass/classclass.h"
#include "runtime/valueobject.h"
#include "common/utility.h"

RootClass::RootClass(Esther *esther, const std::string &name, Ptr<Class> superclass)
    : Class(esther, name, superclass) {
    esther->registerRootClass(this);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body) {
    Ptr<RootClass> _this = this;

    _this->defFunc(esther, name, std::list<Ptr<Class>>(), body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body) {
    Ptr<RootClass> _this = this;

    std::list<Ptr<Class>> paramsClasses;

    for (const std::string &name : paramsClassesNames)
        paramsClasses << esther->getRootClass(name);

    _this->defFunc(esther, name, paramsClasses, body);
}

void RootClass::defFunc(Esther *esther, const std::string &name, const std::list<Ptr<Class>> &paramsClasses, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body) {
    Ptr<RootClass> _this = this;

    std::string className = _this->getName();

    _this->defFunc(esther, name, paramsClasses.size(), [paramsClasses, name, body, className](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        int i = 0;
        for (Class *_class : paramsClasses)
            if (!args[i++]->getClass()->isChild(_class)) {
                Esther::runtimeError(className + "." + name + ": invalid argument");
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body) {
    Ptr<RootClass> _this = this;

    std::string className = _this->getName();

    _this->defFunc(esther, name, arity, [name, body, className](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        for (int i = 0; i < (int)args.size(); i++)
            if (!dynamic_cast<ValueObject *>(*args[i])) {
                Esther::runtimeError(className + "." + name + ": invalid argument #" + Utility::toString(i));
                return nullptr;
            }

        return body(esther, self, args);
    });
}

void RootClass::defFunc(Esther *esther, const std::string &name, int arity, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body) {
    Ptr<RootClass> _this = this;

    std::string className = _this->getName();

    _this->setAttribute(name, new NativeFunction(esther, name, arity, [name, body, className, _this](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
                            if (!self->getClass()->isChild(*_this)) {
                                Esther::runtimeError(className + "." + name + ": invalid self");
                                return nullptr;
                            }

                            return body(esther, self, args);
                        }));
}

void RootClass::defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &)) {
    Ptr<RootClass> _this = this;

    std::string className = _this->getName();

    _this->setAttribute(name, new NativeFunction(esther, name, 1, [name, body, className](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
                            if (!dynamic_cast<ValueObject *>(*self)) {
                                Esther::runtimeError(className + "." + name + ": invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[0])) {
                                Esther::runtimeError(className + "." + name + ": invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, body(((ValueObject *)*self)->getVariant(), ((ValueObject *)*args[0])->getVariant()));
                        }));
}

void RootClass::defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &)) {
    Ptr<RootClass> _this = this;

    std::string className = _this->getName();

    _this->setAttribute(name, new NativeFunction(esther, name, 1, [name, body, className](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
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
