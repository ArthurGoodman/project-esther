#include "esther/object.h"

#include <stdlib.h>

#include "esther/esther.h"
#include "esther/strmap.h"

PObject Object_new(struct Esther *esther) {
    return Object_new_init(esther, NULL);
}

PObject Object_new_init(struct Esther *esther, PClass objectClass) {
    PObject self = malloc(sizeof(struct Object));
    Object_init(esther, self, objectClass);
    return self;
}

void Object_init(struct Esther *esther, PObject self, PClass objectClass) {
    self->objectClass = objectClass == NULL ? esther->objectClass : objectClass;
    self->attributes = NULL;
}

bool Object_hasAttribute(PObject self, const char *name) {
    return self->attributes && strmap_contains(self->attributes, name);
}

PObject Object_getAttribute(PObject self, const char *name) {
    return self->attributes ? strmap_get(self->attributes, name) : NULL;
}

void Object_setAttribute(PObject self, const char *name, PObject value) {
    if (!self->attributes)
        self->attributes = strmap_new();

    strmap_set(self->attributes, name, value);
}
