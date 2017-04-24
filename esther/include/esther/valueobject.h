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

ValueObject *ValueObject_new_char(Esther *esther, char value);
ValueObject *ValueObject_new_int(Esther *esther, int value);
ValueObject *ValueObject_new_real(Esther *esther, double value);
ValueObject *ValueObject_new_var(Esther *esther, Variant value);

void ValueObject_init(Esther *esther, ValueObject *self, Variant value);

Variant ValueObject_getValue(ValueObject *self);

String *ValueObject_virtual_toString(Esther *esther, Object *self);

bool ValueObject_virtual_equals(Esther *esther, Object *self, Object *obj);

Class *ValueObject_variantTypeToObjectClass(Esther *esther, VariantType type);

#ifdef __cplusplus
}
#endif
