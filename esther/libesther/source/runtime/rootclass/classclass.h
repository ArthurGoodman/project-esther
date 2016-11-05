#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
public:
    Object *createClass(const std::string &name, Class *superclass = nullptr);

    void setupMethods();
};
