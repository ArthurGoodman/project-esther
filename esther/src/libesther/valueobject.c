#include "esther/valueobject.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *ValueObject_new_char(Esther *es, char value) {
    return ValueObject_new_var(es, Variant_char(value));
}

Object *ValueObject_new_int(Esther *es, int value) {
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

static VTableForObject ValueObject_vtable = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = Object_virtual_finalize },
    .toString = ValueObject_virtual_toString,
    .inspect = ValueObject_virtual_inspect,
    .equals = ValueObject_virtual_equals,
    .isTrue = Object_virtual_isTrue
};

void ValueObject_init(Esther *es, Object *self, Variant value) {
    Object_init(es, self, TValueObject, ValueObject_variantTypeToObjectClass(es, value.type));

    as_ValueObject(self)->value = value;

    *(void **) self = &ValueObject_vtable;
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
    return Object_getType(obj) == TValueObject && Variant_eq(as_ValueObject(self)->value, as_ValueObject(self)->value);
}

Object *ValueObject_variantTypeToObjectClass(Esther *es, VariantType type) {
    switch (type) {
    case CharVariant:
        return es->charClass;

    case IntVariant:
        return es->intClass;

    case RealVariant:
        return es->floatClass;

    default:
        return NULL;
    }
}
