#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

struct strmap;

struct Class;
struct Esther;

struct Object {
    struct Class *objectClass;
    struct strmap *attributes;
};

typedef struct Object *PObject;
typedef struct Class *PClass;

PObject Object_new(struct Esther *esther);
PObject Object_new_init(struct Esther *esther, PClass objectClass);

void Object_init(struct Esther *esther, PObject self, PClass objectClass);

bool Object_hasAttribute(PObject self, const char *name);
PObject Object_getAttribute(PObject self, const char *name);
void Object_setAttribute(PObject self, const char *name, PObject value);

#ifdef __cplusplus
}
#endif
