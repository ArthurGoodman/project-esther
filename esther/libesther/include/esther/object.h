#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct strmap;

struct Class;
struct Esther;

struct Object {
    struct Class *objectClass;
    struct strmap *attributes;
};

struct Object *Object_new(struct Esther *esther);
void Object_init(struct Esther *esther, struct Object *volatile self);

bool Object_hasAttribute(struct Object *volatile self, const char *name);
struct Object *Object_getAttribute(struct Object *volatile self, const char *name);
void Object_setAttribute(struct Object *volatile self, const char *name, struct Object *volatile value);

#ifdef __cplusplus
}
#endif
