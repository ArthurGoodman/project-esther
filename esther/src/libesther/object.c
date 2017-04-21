#include "esther/object.h"

#include <stdlib.h>

#include "esther/esther.h"
#include "esther/std_string_map.h"

Object *Object_new(Esther *esther) {
    return Object_new_init(esther, NULL);
}

Object *Object_new_init(Esther *esther, Class *objectClass) {
    Object *self = malloc(sizeof(Object));
    Object_init(esther, self, objectClass);
    return self;
}

void Object_init(Esther *esther, Object *self, Class *objectClass) {
    self->objectClass = objectClass == NULL ? esther->objectClass : objectClass;
    self->attributes = NULL;
}

bool Object_hasAttribute(Object *self, const char *name) {
    return self->attributes && std_string_map_contains(self->attributes, name);
}

Object *Object_getAttribute(Object *self, const char *name) {
    return self->attributes ? std_string_map_get(self->attributes, name) : NULL;
}

void Object_setAttribute(Object *self, const char *name, Object *value) {
    if (!self->attributes)
        self->attributes = std_string_map_new();

    std_string_map_set(self->attributes, name, value);
}
