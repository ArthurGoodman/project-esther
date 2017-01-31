#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
    friend class Esther;

public:
    Pointer<Object> createObject(Pointer<Class> objectClass);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    ObjectClass(Esther *esther);
};
