#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
    friend class Esther;

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    BooleanClass(Esther *esther);
};
