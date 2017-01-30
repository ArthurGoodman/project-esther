#pragma once

#include <functional>
#include <list>

#include "class.h"
#include "variant.h"

class Esther;

class RootClass : public Class {
    friend class Esther;

protected:
    RootClass(Esther *esther, const std::string &name, Pointer<Class> superclass);

    virtual void setupMethods(Esther *esther) = 0;

    void defFunc(Esther *esther, const std::string &name, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<Pointer<Class>> &paramsClasses, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    void defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body);
    void defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &));
    void defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &));
};
