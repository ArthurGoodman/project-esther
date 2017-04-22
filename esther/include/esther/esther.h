#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"

typedef struct Esther {
    Class *objectClass;
    Class *classClass;
    Class *stringClass;
    Class *functionClass;
    Class *tupleClass;

    Object *mainObject;
    Object *trueObject;
    Object *falseObject;
} Esther;

void Esther_init(Esther *self);

#ifdef __cplusplus
}
#endif
