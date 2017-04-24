#include "esther/object.h"

#include <stdlib.h>

#include "esther/esther.h"
#include "esther/function.h"
#include "esther/id.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"

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

    self->toString = Object_virtual_toString;
    self->inspect = Object_virtual_toString;
    self->equals = Object_virtual_equals;
    self->isTrue = Object_virtual_isTrue;
}

Class *Object_getClass(Object *self) {
    return self->objectClass;
}

bool Object_hasAttribute(Object *self, const char *name) {
    return self->attributes && std_map_contains(self->attributes, (const void *)stringToId(name));
}

Object *Object_getAttribute(Object *self, const char *name) {
    return self->attributes ? std_map_get(self->attributes, (const void *)stringToId(name)) : NULL;
}

void Object_setAttribute(Object *self, const char *name, Object *value) {
    if (!self->attributes)
        self->attributes = std_map_new(ulong_compare);

    std_map_set(self->attributes, (const void *)stringToId(name), value);
}

bool Object_is(Object *self, Class *_class) {
    return Class_isChildOf(self->objectClass, _class);
}

Object *Object_resolve(Object *self, const char *name) {
    return Object_hasAttribute(self, name) ? Object_getAttribute(self, name) : Class_lookup(self->objectClass, name);
}

Object *Object_call(Esther *esther, Object *self, const char *name, Tuple *args) {
    Object *f = Object_resolve(self, name);

    if (!f)
        return NULL;

    return Object_call_function(esther, self, f, args);
}

Object *Object_callIfFound(Esther *esther, Object *self, const char *name, Tuple *args) {
    Object *f = Object_resolve(self, name);

    if (!f)
        return NULL;

    return Object_call_function(esther, self, f, args);
}

Object *Object_call_function(Esther *esther, Object *self, Object *f, Tuple *args) {
    if (Object_is(f, esther->functionClass))
        return Function_invoke(esther, (Function *)f, self, args);

    return Object_call(esther, f, "()", Tuple_new(esther, 2, self, args));
}

String *Object_toString(Esther *esther, Object *self) {
    return self->toString(esther, self);
}

String *Object_virtual_toString(Esther *esther, Object *self) {
    return String_new_std(esther, std_string_format("<%s:0x%lx>", Class_getName(self->objectClass), self));
}

String *Object_inspect(Esther *esther, Object *self) {
    return self->inspect(esther, self);
}

bool Object_equals(Esther *esther, Object *self, Object *obj) {
    return self->equals(esther, self, obj);
}

bool Object_virtual_equals(Esther *UNUSED(esther), Object *self, Object *obj) {
    return self == obj;
}

bool Object_isTrue(Object *self) {
    return self->isTrue();
}

bool Object_virtual_isTrue() {
    return true;
}
