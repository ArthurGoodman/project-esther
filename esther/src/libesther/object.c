#include "esther/object.h"

#include "esther/class.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/function.h"
#include "esther/std_map.h"
#include "esther/string.h"
#include "esther/tuple.h"

Object *Object_virtual_clone_unimplemented(Esther *es, Object *self) {
    Exception_throw_new(es, "cannot clone objects of %s class", Class_getName(Object_getClass(self)).data);
    return NULL;
}

Object *Object_new(Esther *es) {
    Object *self = gc_alloc(sizeof(Object));
    Object_init(es, self, TObject, NULL);
    return self;
}

NONSTATIC_OBJECT_VTABLE(Object)

void Object_init(Esther *es, Object *self, ObjectType type, Object *objectClass) {
    ManagedObject_init(&self->base);

    self->type = type;
    self->objectClass = objectClass ? objectClass : Esther_getRootObject(es, c_str_to_id("Object"));
    self->attributes = NULL;

    *(void **) self = &vtable_for_Object;
}

ObjectType Object_getType(Object *self) {
    return self->type;
}

Object *Object_getClass(Object *self) {
    return self->objectClass;
}

bool Object_hasAttribute(Object *self, ID id) {
    return self->attributes && std_map_contains(self->attributes, (void *) id);
}

Object *Object_getAttribute(Object *self, ID id) {
    return self->attributes ? std_map_get(self->attributes, (void *) id) : NULL;
}

void Object_setAttribute(Object *self, ID id, Object *value) {
    if (!self->attributes)
        self->attributes = std_map_new(compare_id);

    std_map_set(self->attributes, (void *) id, value);
}

bool Object_is(Object *self, Object *_class) {
    return Class_isChildOf(self->objectClass, _class);
}

Object *Object_resolve(Object *self, ID id) {
    return Object_hasAttribute(self, id) ? Object_getAttribute(self, id) : Class_lookup(self->objectClass, id);
}

Object *Object_call(Esther *es, Object *self, ID id, size_t n, ...) {
    va_list ap;
    va_start(ap, n);

    Object *value = Object_call_args(es, self, id, Tuple_new_va(es, n, ap));

    va_end(ap);

    return value;
}

Object *Object_call_args(Esther *es, Object *self, ID id, Object *args) {
    Object *f = Object_resolve(self, id);

    if (!f) {
        Exception_throw_new(es, "undefined attribute '%s'", id_to_str(id).data);
        return NULL;
    }

    return Object_callFunction(es, self, f, args);
}

Object *Object_callFunction(Esther *es, Object *self, Object *f, Object *args) {
    if (Object_getType(f) == TFunction)
        return Function_invoke(es, f, self, args);

    return Object_call(es, f, c_str_to_id("()"), 2, self, args);
}

Object *Object_toString(Esther *es, Object *self) {
    return (*(ObjectVTable **) self)->toString(es, self);
}

Object *Object_virtual_toString(Esther *es, Object *self) {
    return String_new_move(es, string_format("<%s:0x%lx>", Class_getName(self->objectClass).data, self));
}

Object *Object_inspect(Esther *es, Object *self) {
    return (*(ObjectVTable **) self)->inspect(es, self);
}

bool Object_equals(Object *self, Object *obj) {
    return (*(ObjectVTable **) self)->equals(self, obj);
}

bool Object_virtual_equals(Object *self, Object *obj) {
    return self == obj;
}

bool Object_less(Object *self, Object *obj) {
    return (*(ObjectVTable **) self)->less(self, obj);
}

bool Object_virtual_less(Object *self, Object *obj) {
    return self < obj;
}

bool Object_isTrue(Object *self) {
    return (*(ObjectVTable **) self)->isTrue(self);
}

bool Object_virtual_isTrue(Object *UNUSED(self)) {
    return true;
}

void Object_copyAttributes(Object *self, Object *target) {
    if (!self->attributes)
        return;

    std_map_iterator i;
    std_map_begin(self->attributes, &i);

    while (!std_map_end(self->attributes, &i)) {
        Object_setAttribute(target, (ID) std_map_iterator_key(&i), std_map_iterator_value(&i));
        std_map_iterator_next(&i);
    }
}

Object *Object_clone(Esther *es, Object *self) {
    return (*(ObjectVTable **) self)->clone(es, self);
}

Object *Object_virtual_clone(Esther *es, Object *self) {
    Object *clone = Object_new(es);
    clone->objectClass = self->objectClass;
    Object_copyAttributes(self, clone);
    return clone;
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
