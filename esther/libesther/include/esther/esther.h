#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

struct Object;
struct Class;

struct Esther {
    struct Class *objectClass;
    struct Class *classClass;
    struct Class *functionClass;

    struct Object *mainObject;
    struct Object *trueObject;
    struct Object *falseObject;
};

struct Esther *Esther_new();

#ifdef __cplusplus
}
#endif
