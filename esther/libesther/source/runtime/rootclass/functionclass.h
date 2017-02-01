#pragma once

#include <functional>
#include <list>

#include "rootclass.h"

class Expression;
class Context;
class Function;

class FunctionClass : public RootClass {
public:
    FunctionClass(Esther *esther);

    void setupMethods(Esther *esther);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);
};
