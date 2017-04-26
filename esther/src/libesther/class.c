#include "esther/class.h"

#include "esther/esther.h"
#include "esther/function.h"
#include "esther/id.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Class_new(Esther *esther) {
    return Class_new_init(esther, "", NULL);
}

Object *Class_new_init(Esther *esther, const char *name, Object *superclass) {
    Object *self = malloc(sizeof(Class));
    Class_init(esther, self, name, superclass);
    return self;
}

void Class_init(Esther *esther, Object *self, const char *name, Object *superclass) {
    Object_init(esther, self, esther->classClass);

    as_class(self)->name = strdup(name);
    as_class(self)->superclass = superclass ? superclass : esther->objectClass;
    as_class(self)->methods = NULL;

    as_class(self)->newInstance = Class_virtual_newInstance;
    as_class(self)->base.toString = Class_virtual_toString;
    as_class(self)->base.inspect = Class_virtual_toString;
}

const char *Class_getName(Object *self) {
    return as_class(self)->name;
}

Object *Class_getSuperclass(Object *self) {
    return as_class(self)->superclass;
}

bool Class_hasMethod(Object *self, const char *name) {
    return as_class(self)->methods && std_map_contains(as_class(self)->methods, (const void *)stringToId(name));
}

Object *Class_getMethod(Object *self, const char *name) {
    return as_class(self)->methods ? std_map_get(as_class(self)->methods, (const void *)stringToId(name)) : NULL;
}

void Class_setMethod(Object *self, const char *name, Object *method) {
    if (!as_class(self)->methods)
        as_class(self)->methods = std_map_new(ulong_compare);

    std_map_set(as_class(self)->methods, (const void *)stringToId(name), method);
}

void Class_setMethod_func(Object *self, Object *f) {
    Class_setMethod(self, Function_getName(f), f);
}

bool Class_isChildOf(Object *self, Object *_class) {
    return self == _class || (as_class(self)->superclass && Class_isChildOf(as_class(self)->superclass, _class));
}

Object *Class_lookup(Object *self, const char *name) {
    if (Class_hasMethod(self, name))
        return Class_getMethod(self, name);

    if (as_class(self)->superclass)
        return Class_lookup(as_class(self)->superclass, name);

    return NULL;
}

Object *Class_virtual_toString(Esther *esther, Object *self) {
    const char *name = as_class(self)->name;

    if (strlen(name) == 0)
        return String_new(esther, "<anonymous class>");

    return String_new_std(esther, std_string_format("<class %s>", name));
}

Object *Class_newInstance(Esther *esther, Object *self, Object *args) {
    Object *instance = as_class(self)->newInstance(esther, self, args);
    Object_callIfFound(esther, instance, "initialize", args);
    return instance;
}

Object *Class_virtual_newInstance(Esther *esther, Object *self, Object *args) {
    Object *instance = Class_newInstance(esther, as_class(self)->superclass, args);
    instance->objectClass = self;
    return instance;
}
