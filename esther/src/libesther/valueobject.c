#include "esther/valueobject.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *ValueObject_new_char(Esther *esther, char value) {
    return ValueObject_new_var(esther, Variant_create_char(value));
}

Object *ValueObject_new_int(Esther *esther, int value) {
    return ValueObject_new_var(esther, Variant_create_int(value));
}

Object *ValueObject_new_real(Esther *esther, double value) {
    return ValueObject_new_var(esther, Variant_create_real(value));
}

Object *ValueObject_new_var(Esther *esther, Variant value) {
    Object *self = malloc(sizeof(ValueObject));
    ValueObject_init(esther, self, value);
    return self;
}

void ValueObject_init(Esther *esther, Object *self, Variant value) {
    Object_init(esther, self, ValueObject_variantTypeToObjectClass(esther, value.type));

    as_valueObject(self)->value = value;

    as_valueObject(self)->base.toString = ValueObject_virtual_toString;
    as_valueObject(self)->base.inspect = ValueObject_virtual_toString;
    as_valueObject(self)->base.equals = ValueObject_virtual_equals;
}

Variant ValueObject_getValue(Object *self) {
    return as_valueObject(self)->value;
}

Object *ValueObject_virtual_toString(Esther *esther, Object *self) {
    return String_new_std(esther, Variant_toString(as_valueObject(self)->value));
}

bool ValueObject_virtual_equals(Esther *esther, Object *self, Object *obj) {
    return Object_is(obj, esther->numericClass) && Variant_eq(as_valueObject(self)->value, as_valueObject(self)->value);
}

Object *ValueObject_variantTypeToObjectClass(Esther *esther, VariantType type) {
    switch (type) {
    case CharVariant:
        return esther->charClass;

    case IntVariant:
        return esther->intClass;

    case RealVariant:
        return esther->floatClass;

    default:
        return NULL;
    }
}
