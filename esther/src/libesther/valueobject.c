#include "esther/valueobject.h"

#include "esther/esther.h"
#include "esther/string.h"

ValueObject *ValueObject_new_char(Esther *esther, char value) {
    return ValueObject_new_var(esther, Variant_create_char(value));
}

ValueObject *ValueObject_new_int(Esther *esther, int value) {
    return ValueObject_new_var(esther, Variant_create_int(value));
}

ValueObject *ValueObject_new_real(Esther *esther, double value) {
    return ValueObject_new_var(esther, Variant_create_real(value));
}

ValueObject *ValueObject_new_var(Esther *esther, Variant value) {
    ValueObject *self = malloc(sizeof(ValueObject));
    ValueObject_init(esther, self, value);
    return self;
}

void ValueObject_init(Esther *esther, ValueObject *self, Variant value) {
    Object_init(esther, &self->base, ValueObject_variantTypeToObjectClass(esther, value.type));

    self->value = value;

    self->base.toString = ValueObject_virtual_toString;
    self->base.inspect = ValueObject_virtual_toString;
    self->base.equals = ValueObject_virtual_equals;
}

Variant ValueObject_getValue(ValueObject *self) {
    return self->value;
}

String *ValueObject_virtual_toString(Esther *esther, Object *self) {
    return String_new_init_std(esther, Variant_toString(((ValueObject *)self)->value));
}

bool ValueObject_virtual_equals(Esther *esther, Object *self, Object *obj) {
    return Object_is(obj, esther->numericClass) && Variant_eq(((ValueObject *)self)->value, ((ValueObject *)obj)->value);
}

Class *ValueObject_variantTypeToObjectClass(Esther *esther, VariantType type) {
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
