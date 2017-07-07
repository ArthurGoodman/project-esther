#include "esther/class.h"

#include "esther/esther.h"
#include "esther/function.h"
#include "esther/id.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Class_new(Esther *es) {
    return Class_new_init(es, string_const(""), NULL);
}

Object *Class_new_init(Esther *es, struct string name, Object *superclass) {
    Object *self = gc_alloc(sizeof(Class));
    Class_init(es, self, name, superclass);
    return self;
}

static VTableForClass Class_vtable = {
    .base = {
        .base = {
            .base = {
                .mapOnRefs = Class_virtual_mapOnRefs },
            .finalize = Class_virtual_finalize },
        .toString = Class_virtual_toString,
        .inspect = Class_virtual_toString,
        .equals = Object_virtual_equals,
        .isTrue = Object_virtual_isTrue },
    .newInstance = Class_virtual_newInstance
};

void Class_init(Esther *es, Object *self, struct string name, Object *superclass) {
    Object_init(es, self, TClass, es->classClass);

    as_Class(self)->name = string_copy(name);
    as_Class(self)->superclass = superclass ? superclass : es->objectClass;
    as_Class(self)->methods = NULL;

    *(void **) self = &Class_vtable;
}

struct string Class_getName(Object *self) {
    return as_Class(self)->name;
}

Object *Class_getSuperclass(Object *self) {
    return as_Class(self)->superclass;
}

bool Class_hasMethod(Object *self, struct string name) {
    return as_Class(self)->methods && std_map_contains(as_Class(self)->methods, (const void *) str_to_id(name));
}

Object *Class_getMethod(Object *self, struct string name) {
    return as_Class(self)->methods ? std_map_get(as_Class(self)->methods, (const void *) str_to_id(name)) : NULL;
}

void Class_setMethod(Object *self, struct string name, Object *method) {
    if (!as_Class(self)->methods)
        as_Class(self)->methods = std_map_new(compare_id);

    std_map_set(as_Class(self)->methods, (const void *) str_to_id(name), method);
}

void Class_setMethod_func(Object *self, Object *f) {
    Class_setMethod(self, Function_getName(f), f);
}

bool Class_isChildOf(Object *self, Object *_class) {
    return self == _class || (as_Class(self)->superclass && Class_isChildOf(as_Class(self)->superclass, _class));
}

Object *Class_lookup(Object *self, struct string name) {
    if (Class_hasMethod(self, name))
        return Class_getMethod(self, name);

    if (as_Class(self)->superclass)
        return Class_lookup(as_Class(self)->superclass, name);

    return NULL;
}

Object *Class_virtual_toString(Esther *es, Object *self) {
    struct string name = as_Class(self)->name;

    if (name.size == 0)
        return String_new_c_str(es, "<anonymous class>");

    // @Temp: C-string
    return String_new_move(es, string_format("<class %s>", name.data));
}

Object *Class_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = (*(VTableForClass **) self)->newInstance(es, self, args);
    Object_callIfFound(es, instance, string_const("initialize"), args);
    return instance;
}

Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = (*(VTableForClass **) as_Class(self)->superclass)->newInstance(es, as_Class(self)->superclass, args);
    instance->objectClass = self;
    return instance;
}

void Class_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(as_Class(self)->superclass);

    if (as_Class(self)->methods) {
        std_map_iterator i;
        std_map_begin(as_Class(self)->methods, &i);

        while (!std_map_end(as_Class(self)->methods, &i)) {
            f(std_map_iterator_value(&i));
            std_map_iterator_next(&i);
        }
    }
}

void Class_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(as_Class(self)->name);
    std_map_delete(as_Class(self)->methods);
}
