#include "esther/valueobject.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *ValueObject_new_char(Esther *es, char value) {
    return ValueObject_new_var(es, Variant_char(value));
}

Object *ValueObject_new_int(Esther *es, int64_t value) {
    return ValueObject_new_var(es, Variant_int(value));
}

Object *ValueObject_new_real(Esther *es, double value) {
    return ValueObject_new_var(es, Variant_real(value));
}

Object *ValueObject_new_var(Esther *es, Variant value) {
    Object *self = gc_alloc(sizeof(ValueObject));
    ValueObject_init(es, self, value);
    return self;
}

static ObjectVTable vtable_for_ValueObject = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = Object_virtual_finalize },
    .toString = ValueObject_virtual_toString,
    .inspect = ValueObject_virtual_inspect,
    .equals = ValueObject_virtual_equals,
    .less = ValueObject_virtual_less,
    .isTrue = Object_virtual_isTrue,
    .clone = ValueObject_virtual_clone
};

void ValueObject_init(Esther *es, Object *self, Variant value) {
    Object_init(es, self, TValueObject, ValueObject_variantTypeToObjectClass(es, value.type));

    as_ValueObject(self)->value = value;

    *(void **) self = &vtable_for_ValueObject;
}

Variant ValueObject_getValue(Object *self) {
    return as_ValueObject(self)->value;
}

void ValueObject_setValue(Object *self, Variant value) {
    as_ValueObject(self)->value = Variant_convertTo(value, Variant_getType(value));
}

Object *ValueObject_virtual_toString(Esther *es, Object *self) {
    return String_new_move(es, Variant_toString(as_ValueObject(self)->value));
}

Object *ValueObject_virtual_inspect(Esther *es, Object *self) {
    return String_new_move(es, Variant_inspect(as_ValueObject(self)->value));
}

bool ValueObject_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TValueObject ? Variant_eq(as_ValueObject(self)->value, as_ValueObject(obj)->value) : Object_virtual_equals(self, obj);
}

bool ValueObject_virtual_less(Object *self, Object *obj) {
    return Object_getType(obj) == TValueObject ? Variant_lt(as_ValueObject(self)->value, as_ValueObject(obj)->value) : Object_virtual_less(self, obj);
}

Object *ValueObject_virtual_clone(Esther *es, Object *self) {
    Object *clone = ValueObject_new_var(es, as_ValueObject(self)->value);
    Object_copyAttributes(self, clone);
    return clone;
}

Object *ValueObject_variantTypeToObjectClass(Esther *es, VariantType type) {
    switch (type) {
    case CharVariant:
        return Esther_getRootObject(es, c_str_to_id("Char"));

    case IntVariant:
        return Esther_getRootObject(es, c_str_to_id("Int"));

    case RealVariant:
        return Esther_getRootObject(es, c_str_to_id("Float"));

    default:
        return NULL;
    }
}
