#pragma once

#include <functional>
#include <list>

#include "runtime/class.h"
#include "variant/variant.h"

namespace es {

class Esther;

class RootClass : public Class {
public:
    virtual void setupMethods(Esther *esther) = 0;

protected:
    RootClass(Esther *esther, const std::string &name, Class *volatile superclass);

    void defFunc(Esther *esther, const std::string &name, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body);
    void defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> &body);
    void defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &));
    void defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &));
};
}
