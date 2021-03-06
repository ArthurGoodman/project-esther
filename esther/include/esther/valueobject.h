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

#define as_ValueObject(obj) ((ValueObject *) obj)

Object *ValueObject_new_char(Esther *es, char value);
Object *ValueObject_new_int(Esther *es, int64_t value);
Object *ValueObject_new_real(Esther *es, double value);
Object *ValueObject_new_var(Esther *es, Variant value);

void ValueObject_init(Esther *es, Object *self, Variant value);

Variant ValueObject_getValue(Object *self);
void ValueObject_setValue(Object *self, Variant value);

Object *ValueObject_virtual_toString(Esther *es, Object *self);
Object *ValueObject_virtual_inspect(Esther *es, Object *self);

bool ValueObject_virtual_equals(Object *self, Object *obj);

bool ValueObject_virtual_less(Object *self, Object *obj);

Object *ValueObject_virtual_clone(Esther *es, Object *self);

Object *ValueObject_variantTypeToObjectClass(Esther *es, VariantType type);

#ifdef __cplusplus
}
#endif
