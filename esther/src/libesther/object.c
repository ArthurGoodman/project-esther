#include "esther/object.h"

#include <stdlib.h>

#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/function.h"
#include "esther/id.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"

Object *Object_new(Esther *es) {
    Object *self = gc_alloc(sizeof(Object));
    Object_init(es, self, TObject, es->objectClass);
    return self;
}

static VTableForObject Object_vtable = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = Object_virtual_finalize },
    .toString = Object_virtual_toString,
    .inspect = Object_virtual_toString,
    .equals = Object_virtual_equals,
    .isTrue = Object_virtual_isTrue
};

void Object_init(Esther *UNUSED(es), Object *self, ObjectType type, Object *objectClass) {
    ManagedObject_init(&self->base);

    self->type = type;
    self->objectClass = objectClass;
    self->attributes = NULL;

    *(void **) self = &Object_vtable;
}

ObjectType Object_getType(Object *self) {
    return self->type;
}

Object *Object_getClass(Object *self) {
    return self->objectClass;
}

bool Object_hasAttribute(Object *self, struct string name) {
    return self->attributes && std_map_contains(self->attributes, (const void *) str_to_id(name));
}

Object *Object_getAttribute(Object *self, struct string name) {
    return self->attributes ? std_map_get(self->attributes, (const void *) str_to_id(name)) : NULL;
}

void Object_setAttribute(Object *self, struct string name, Object *value) {
    if (!self->attributes)
        self->attributes = std_map_new(compare_id);

    std_map_set(self->attributes, (const void *) str_to_id(name), value);
}

bool Object_is(Object *self, Object *_class) {
    return Class_isChildOf(self->objectClass, _class);
}

Object *Object_resolve(Object *self, struct string name) {
    return Object_hasAttribute(self, name) ? Object_getAttribute(self, name) : Class_lookup(self->objectClass, name);
}

Object *Object_call(Esther *es, Object *self, struct string name, Object *args) {
    Object *f = Object_resolve(self, name);

    if (!f) {
        //@Temp: C-string
        Exception_throw_new(es, "undefined attribute '%s'", name.data);
        return NULL;
    }

    return Object_call_function(es, self, f, args);
}

Object *Object_callIfFound(Esther *es, Object *self, struct string name, Object *args) {
    Object *f = Object_resolve(self, name);

    if (!f)
        return NULL;

    return Object_call_function(es, self, f, args);
}

Object *Object_call_function(Esther *es, Object *self, Object *f, Object *args) {
    if (Object_getType(f) == TFunction)
        return Function_invoke(es, f, self, args);

    return Object_call(es, f, string_const("()"), Tuple_new(es, 2, self, args));
}

Object *Object_toString(Esther *es, Object *self) {
    return (*(VTableForObject **) self)->toString(es, self);
}

Object *Object_virtual_toString(Esther *es, Object *self) {
    return String_new_move(es, string_format("<%s:0x%lx>", Class_getName(self->objectClass).data, self));
}

Object *Object_inspect(Esther *es, Object *self) {
    return (*(VTableForObject **) self)->inspect(es, self);
}

bool Object_equals(Object *self, Object *obj) {
    return (*(VTableForObject **) self)->equals(self, obj);
}

bool Object_virtual_equals(Object *self, Object *obj) {
    return self == obj;
}

bool Object_isTrue(Object *self) {
    return (*(VTableForObject **) self)->isTrue();
}

bool Object_virtual_isTrue() {
    return true;
}

void Object_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    f(as_Object(self)->objectClass);

    if (as_Object(self)->attributes) {
        std_map_iterator i;
        std_map_begin(as_Object(self)->attributes, &i);

        while (!std_map_end(as_Object(self)->attributes, &i)) {
            f(std_map_iterator_value(&i));
            std_map_iterator_next(&i);
        }
    }
}

void Object_virtual_finalize(ManagedObject *self) {
    std_map_delete(as_Object(self)->attributes);
}
