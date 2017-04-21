#include "esther/class.h"

#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/std_string_map.h"

Class *Class_new(Esther *esther) {
    return Class_new_init(esther, "", NULL);
}

Class *Class_new_init(Esther *esther, const char *name, Class *superclass) {
    Class *self = malloc(sizeof(Class));
    Class_init(esther, self, name, superclass);
    return self;
}

void Class_init(Esther *esther, Class *self, const char *name, Class *superclass) {
    Object_init(esther, &self->base, esther->classClass);
    self->name = std_string_new_init(name);
    self->superclass = superclass ? superclass : esther->objectClass;
    self->methods = NULL;
}

void Class_add_method(Class *self, const char *name, Object *method) {
    if (!self->methods)
        self->methods = std_string_map_new();

    std_string_map_set(self->methods, name, method);
}
