#include "esther/class.h"

#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/function.h"
#include "esther/std_map.h"
#include "esther/string.h"

Object *Class_virtual_unimplemented_newInstance(Esther *es, Object *self, Object *UNUSED(args)) {
    Exception_throw_new(es, "cannot create an instance of %s class", Class_getName(self).data);
    return NULL;
}

Object *Class_new(Esther *es, struct string name, Object *superclass) {
    Object *self = gc_alloc(sizeof(Class));
    Class_init(es, self, name, superclass);
    return self;
}

Object *Class_new_anonymous(Esther *es) {
    return Class_new(es, string_const(""), NULL);
}

CLASS_VTABLE()

void Class_init(Esther *es, Object *self, struct string name, Object *superclass) {
    Object_init(es, self, TClass, Esther_getRootObject(es, cstr_to_id("Class")));

    as_Class(self)->name = string_copy(name);
    as_Class(self)->superclass = superclass ? superclass : Esther_getRootObject(es, cstr_to_id("Object"));
    as_Class(self)->methods = NULL;

    *(void **) self = &vtable_for_Class;
}

struct string Class_getName(Object *self) {
    return as_Class(self)->name;
}

Object *Class_getSuperclass(Object *self) {
    return as_Class(self)->superclass;
}

bool Class_hasMethod(Object *self, ID id) {
    return as_Class(self)->methods && std_map_contains(as_Class(self)->methods, (const void *) id);
}

Object *Class_getMethod(Object *self, ID id) {
    return as_Class(self)->methods ? std_map_get(as_Class(self)->methods, (const void *) id) : NULL;
}

void Class_setMethod(Object *self, ID id, Object *method) {
    if (!as_Class(self)->methods)
        as_Class(self)->methods = std_map_new(compare_id);

    std_map_set(as_Class(self)->methods, (const void *) id, method);
}

void Class_setMethod_func(Object *self, Object *f) {
    Class_setMethod(self, str_to_id(Function_getName(f)), f);
}

bool Class_isChildOf(Object *self, Object *_class) {
    return self == _class || (as_Class(self)->superclass && Class_isChildOf(as_Class(self)->superclass, _class));
}

Object *Class_lookup(Object *self, ID id) {
    if (Class_hasMethod(self, id))
        return Class_getMethod(self, id);

    if (as_Class(self)->superclass)
        return Class_lookup(as_Class(self)->superclass, id);

    return NULL;
}

Object *Class_virtual_toString(Esther *es, Object *self) {
    struct string name = as_Class(self)->name;

    if (name.size == 0)
        return String_new_cstr(es, "<anonymous class>");

    return String_new_move(es, string_format("<class %s>", name.data));
}

Object *Class_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = (*(ClassVTable **) self)->newInstance(es, self, args);

    Object *initialize = Object_resolve(instance, cstr_to_id("initialize"));

    if (initialize)
        Object_callFunction(es, instance, initialize, args);

    return instance;
}

Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args) {
    Object *instance = (*(ClassVTable **) as_Class(self)->superclass)->newInstance(es, as_Class(self)->superclass, args);
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
