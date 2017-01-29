#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
    friend class Esther;

public:
    Object *createObject(Class *objectClass);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    ObjectClass(Esther *esther);
};
