#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct Class {
    struct Object object;
    struct strmap *methods;
};

struct Class *Class_new(struct Esther *esther);
void Class_init(struct Esther *esther, struct Class *volatile self);

#ifdef __cplusplus
}
#endif
