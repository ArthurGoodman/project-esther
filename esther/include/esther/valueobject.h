#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/variant.h"

typedef struct ValueObject {
    Object base;

    Variant value;
} ValueObject;

#define as_valueObject(obj) ((ValueObject *)obj)

Object *ValueObject_new_char(Esther *esther, char value);
Object *ValueObject_new_int(Esther *esther, int value);
Object *ValueObject_new_real(Esther *esther, double value);
Object *ValueObject_new_var(Esther *esther, Variant value);

void ValueObject_init(Esther *esther, Object *self, Variant value);

Variant ValueObject_getValue(Object *self);

Object *ValueObject_virtual_toString(Esther *esther, Object *self);

bool ValueObject_virtual_equals(Esther *esther, Object *self, Object *obj);

Object *ValueObject_variantTypeToObjectClass(Esther *esther, VariantType type);

#ifdef __cplusplus
}
#endif
