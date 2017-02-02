#pragma once

#include <functional>
#include <list>

#include "class.h"
#include "variant.h"

class Esther;

class RootClass : public Class {
public:
    virtual void setupMethods(Esther *esther) = 0;

protected:
    RootClass(Esther *esther, const std::string &name, Ptr<Class> superclass);

    void defFunc(Esther *esther, const std::string &name, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, const std::list<Ptr<Class>> &paramsClasses, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body);
    void defValueObjectFunc(Esther *esther, const std::string &name, int arity, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body);
    void defFunc(Esther *esther, const std::string &name, int arity, const std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> &body);
    void defOper(Esther *esther, const std::string &name, Variant (*body)(const Variant &, const Variant &));
    void defPred(Esther *esther, const std::string &name, bool (*body)(const Variant &, const Variant &));
};
