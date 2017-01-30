#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
    friend class Esther;

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    NullClass(Esther *esther);
};
