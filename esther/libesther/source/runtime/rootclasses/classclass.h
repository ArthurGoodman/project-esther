#pragma once

#include "class.h"

class ClassClass : public Class {
    friend class Runtime;

public:
    Class *createClass(const std::string &name, Class *superclass = nullptr);

protected:
    Object *createNewInstance();

private:
    ClassClass();
};
