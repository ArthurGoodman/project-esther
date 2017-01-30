#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
    friend class Esther;

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    BooleanClass(Esther *esther);
};
