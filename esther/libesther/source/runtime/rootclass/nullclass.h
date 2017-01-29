#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
    friend class Esther;

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    NullClass(Esther *esther);
};
