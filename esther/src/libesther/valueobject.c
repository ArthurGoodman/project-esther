#include "esther/valueobject.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *ValueObject_new_char(Esther *es, char value) {
    return ValueObject_new_var(es, Variant_create_char(value));
}

Object *ValueObject_new_int(Esther *es, int value) {
    return ValueObject_new_var(es, Variant_create_int(value));
}

Object *ValueObject_new_real(Esther *es, double value) {
    return ValueObject_new_var(es, Variant_create_real(value));
}

Object *ValueObject_new_var(Esther *es, Variant value) {
    Object *self = malloc(sizeof(ValueObject));
    ValueObject_init(es, self, value);
    return self;
}

void ValueObject_init(Esther *es, Object *self, Variant value) {
    Object_init(es, self, ValueObject_variantTypeToObjectClass(es, value.type));

    as_ValueObject(self)->value = value;

    as_ValueObject(self)->base.toString = ValueObject_virtual_toString;
    as_ValueObject(self)->base.inspect = ValueObject_virtual_toString;
    as_ValueObject(self)->base.equals = ValueObject_virtual_equals;
}

Variant ValueObject_getValue(Object *self) {
    return as_ValueObject(self)->value;
}

Object *ValueObject_virtual_toString(Esther *es, Object *self) {
    return String_new_std(es, Variant_toString(as_ValueObject(self)->value));
}

bool ValueObject_virtual_equals(Esther *es, Object *self, Object *obj) {
    return Object_is(obj, es->numericClass) && Variant_eq(as_ValueObject(self)->value, as_ValueObject(self)->value);
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
