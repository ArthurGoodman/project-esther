#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
    friend class Esther;

public:
    Pointer<Class> createClass(const std::string &name, Pointer<Class> superclass = nullptr);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    ClassClass(Esther *esther);
};
