#pragma once

#include <functional>

#include "class.h"

class Signature;

class RootClass : public Class {
public:
    RootClass(const std::string &name, Class *superclass);
    RootClass(const std::string &name, const std::string &superclassName);
    RootClass(const std::string &name);

    void setMethod(const std::string &name, Signature *signature, std::function<IObject *(IObject *, Tuple *)> body);
    void setStaticMethod(const std::string &name, Signature *signature, std::function<IObject *(IObject *, Tuple *)> body);

    virtual void setupMethods() = 0;
};
