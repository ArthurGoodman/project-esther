#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"

typedef struct Esther {
    Object *mainObject;

    Class *objectClass;
    Class *classClass;
    Class *stringClass;
    Class *symbolClass;
    Class *functionClass;
    Class *tupleClass;
    Class *arrayClass;
    Class *booleanClass;
    Class *nullClass;
    Class *numericClass;
    Class *charClass;
    Class *intClass;
    Class *floatClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;
} Esther;

void Esther_init(Esther *self);

#ifdef __cplusplus
}
#endif
