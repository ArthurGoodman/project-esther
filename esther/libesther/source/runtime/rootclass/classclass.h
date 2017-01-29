#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
    friend class Esther;

public:
    Class *createClass(const std::string &name, Class *superclass = nullptr);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    ClassClass(Esther *esther);
};
