#pragma once

#include <functional>
#include <list>

#include "class.h"
#include "variant.h"

class Runtime;

class RootClass : public Class {
    friend class Runtime;

protected:
    Runtime *runtime;

    RootClass(Runtime *runtime, const std::string &name, Class *superclass);

    virtual void setupMethods() = 0;

    void def(const std::string &name, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
    void def(const std::string &name, const std::list<std::string> &paramsClassesNames, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
    void def(const std::string &name, Variant (*body)(const Variant &, const Variant &));
    void def(const std::string &name, bool (*body)(const Variant &, const Variant &));
    void def(const std::string &name, const std::list<Class *> &paramsClasses, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
};
