#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"

struct Esther {
    PClass objectClass;
    PClass classClass;
    PClass stringClass;
    PClass functionClass;

    PObject mainObject;
    PObject trueObject;
    PObject falseObject;
};

void Esther_init(struct Esther *self);

#ifdef __cplusplus
}
#endif
