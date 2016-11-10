#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
    friend class Runtime;

public:
    Class *createClass(const std::string &name, Class *superclass = nullptr);

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    ClassClass(Runtime *runtime);
};