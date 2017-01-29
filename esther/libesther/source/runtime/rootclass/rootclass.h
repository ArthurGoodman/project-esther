#pragma once

#include <functional>
#include <list>

#include "class.h"
#include "variant.h"

class Esther;

class RootClass : public Class {
    friend class Esther;

protected:
    RootClass(Esther *esther, const std::string &name, Class *superclass);

    virtual void setupMethods(Esther *esther) = 0;

    void defFunc(Esther *esther, const std::string &name, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body);
    void defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body);
    void defFunc(Esther *esther, const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body);
    void defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &));
    void defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &));
};
