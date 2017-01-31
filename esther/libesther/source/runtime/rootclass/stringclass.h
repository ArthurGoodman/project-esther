#pragma once

#include "rootclass.h"

class ValueObject;

class StringClass : public RootClass {
    friend class Esther;

public:
    Pointer<ValueObject> createString(const std::string &value);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    StringClass(Esther *esther);
};
