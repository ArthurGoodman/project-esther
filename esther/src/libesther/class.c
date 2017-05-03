#include "esther/class.h"

#include "esther/esther.h"
#include "esther/function.h"
#include "esther/id.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Class_new(Esther *es) {
    return Class_new_init(es, "", NULL);
}

Object *Class_new_init(Esther *es, const char *name, Object *superclass) {
    Object *self = gc_alloc(sizeof(Class));
    Class_init(es, self, name, superclass);
    return self;
}

void Class_init(Esther *es, Object *self, const char *name, Object *superclass) {
    Object_init(es, self, TClass, es->classClass);

    as_Class(self)->name = strdup(name);
    as_Class(self)->superclass = superclass ? superclass : es->objectClass;
    as_Class(self)->methods = NULL;

    as_Class(self)->newInstance = Class_virtual_newInstance;
    as_Class(self)->base.toString = Class_virtual_toString;
    as_Class(self)->base.inspect = Class_virtual_toString;

    self->base.base.mapOnReferences = Class_virtual_mapOnReferences;
    self->base.finalize = Class_virtual_finalize;
}

const char *Class_getName(Object *self) {
    return as_Class(self)->name;
}

Object *Class_getSuperclass(Object *self) {
    return as_Class(self)->superclass;
}

bool Class_hasMethod(Object *self, const char *name) {
    return as_Class(self)->methods && std_map_contains(as_Class(self)->methods, (const void *)stringToId(name));
}

Object *Class_getMethod(Object *self, const char *name) {
    return as_Class(self)->methods ? std_map_get(as_Class(self)->methods, (const void *)stringToId(name)) : NULL;
}

void Class_setMethod(Object *self, const char *name, Object *method) {
    if (!as_Class(self)->methods)
        as_Class(self)->methods = std_map_new(id_compare);

    std_map_set(as_Class(self)->methods, (const void *)stringToId(name), method);
}

void Class_setMethod_func(Object *self, Object *f) {
    Class_setMethod(self, Function_getName(f), f);
}

bool Class_isChildOf(Object *self, Object *_class) {
    return self == _class || (as_Class(self)->superclass && Class_isChildOf(as_Class(self)->superclass, _class));
}

Object *Class_lookup(Object *self, const char *name) {
    if (Class_hasMethod(self, name))
        return Class_getMethod(self, name);

    if (as_Class(self)->superclass)
        return Class_lookup(as_Class(self)->superclass, name);

    return NULL;
}

Object *Class_virtual_toString(Esther *es, Object *self) {
    const char *name = as_Class(self)->name;

    if (strlen(name) == 0)
        return String_new(es, "<anonymous class>");

    return String_new_std(es, std_string_format("<class %s>", name));
}

Object *Class_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = as_Class(self)->newInstance(es, self, args);
    Object_callIfFound(es, instance, "initialize", args);
    return instance;
}

Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = as_Class(as_Class(self)->superclass)->newInstance(es, as_Class(self)->superclass, args);
    instance->objectClass = self;
    return instance;
}

void Class_virtual_mapOnReferences(Mapper *self, MapFunction f) {
    Object_virtual_mapOnReferences(self, f);

    f((void **)&as_Class(self)->superclass);

    if (as_Class(self)->methods) {
        std_map_iterator i;
        std_map_begin(as_Class(self)->methods, &i);

        while (!std_map_end(as_Class(self)->methods, &i)) {
            void *value = std_map_iterator_value(&i);
            f((void **)&value);
            std_map_iterator_set_value(&i, value);

            std_map_iterator_next(&i);
        }
    }
}

void Class_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    free((void *)as_Class(self)->name);
    std_map_delete(as_Class(self)->methods);
}
