#include "esther/object.h"

#include <stdlib.h>

#include "esther/esther.h"
#include "strmap.h"

struct Object *Object_new(struct Esther *esther) {
    struct Object *volatile self = malloc(sizeof(struct Object));
    Object_init(esther, self);
    return self;
}

void Object_init(struct Esther *esther, struct Object *volatile self) {
    self->objectClass = esther->objectClass;
    self->attributes = NULL;
}

bool Object_hasAttribute(struct Object *volatile self, const char *name) {
    return self->attributes && strmap_contains(self->attributes, name);
}

struct Object *Object_getAttribute(struct Object *volatile self, const char *name) {
    return self->attributes ? strmap_get(self->attributes, name) : NULL;
}

void Object_setAttribute(struct Object *volatile self, const char *name, struct Object *volatile value) {
    if (!self->attributes)
        self->attributes = strmap_new();

    strmap_set(self->attributes, name, value);
}
