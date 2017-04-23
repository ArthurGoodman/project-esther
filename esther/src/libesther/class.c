#include "esther/class.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/string.h"
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

    self->name = strdup(name);
    self->superclass = superclass ? superclass : esther->objectClass;
    self->methods = NULL;

    self->newInstance = Class_virtual_newInstance;
    self->base.toString = Class_virtual_toString;
    self->base.inspect = Class_virtual_toString;
}

const char *Class_getName(Class *self) {
    return self->name;
}

Class *Class_getSuperclass(Class *self) {
    return self->superclass;
}

bool Class_hasMethod(Class *self, const char *name) {
    return self->methods && std_string_map_contains(self->methods, name);
}

Object *Class_getMethod(Class *self, const char *name) {
    return self->methods ? std_string_map_get(self->methods, name) : NULL;
}

void Class_setMethod(Class *self, const char *name, Object *method) {
    if (!self->methods)
        self->methods = std_string_map_new();

    std_string_map_set(self->methods, name, method);
}

bool Class_isChildOf(Class *self, Class *_class) {
    return self == _class || (self->superclass && Class_isChildOf(self->superclass, _class));
}

Object *Class_lookup(Class *self, const char *name) {
    if (Class_hasMethod(self, name))
        return Class_getMethod(self, name);

    if (self->superclass)
        return Class_lookup(self->superclass, name);

    return NULL;
}

String *Class_virtual_toString(Esther *esther, Object *self) {
    const char *name = ((Class *)self)->name;

    if (strlen(name) == 0)
        return String_new_init(esther, "<anonymous class>");

    return String_new_init_std(esther, std_string_format("<class %s>", name));
}

Object *Class_newInstance(Esther *esther, Class *self) {
    return self->newInstance(esther, self);
}

Object *Class_virtual_newInstance(Esther *esther, Class *self) {
    Object *instance = NULL;

    if (self->superclass)
        instance = Class_newInstance(esther, self->superclass);
    else
        instance = Object_new(esther);

    instance->objectClass = self;

    return instance;
}
