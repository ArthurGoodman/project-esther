#include "esther/class.h"

#include "esther/esther.h"
#include "esther/str.h"

PClass Class_new(struct Esther *esther) {
    return Class_new_init(esther, "", NULL);
}

PClass Class_new_init(struct Esther *esther, const char *name, PClass superclass) {
    PClass self = malloc(sizeof(struct Class));
    Class_init(esther, self, name, superclass);
    return self;
}

void Class_init(struct Esther *esther, PClass self, const char *name, PClass superclass) {
    Object_init(esther, &self->base, esther->classClass);
    self->name = string_new_init(name);
    self->superclass = superclass ? superclass : esther->objectClass;
    self->methods = NULL;
}
