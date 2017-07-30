#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/id.h"
#include "esther/object.h"

Object *id_to_sym(Esther *es, ID id);
Object *str_to_sym(Esther *es, struct string str);
Object *c_str_to_sym(Esther *es, const char *str);

typedef struct Symbol {
    Object base;

    ID id;
} Symbol;

#define as_Symbol(obj) ((Symbol *) (obj))

Object *Symbol_new(Esther *es, struct string name);
Object *Symbol_new_c_str(Esther *es, const char *name);
Object *Symbol_new_id(Esther *es, ID id);

void Symbol_init(Esther *es, Object *self, struct string name);
void Symbol_init_c_str(Esther *es, Object *self, const char *name);

ID Symbol_getId(Object *self);

Object *Symbol_virtual_toString(Esther *es, Object *self);
Object *Symbol_virtual_inspect(Esther *es, Object *self);

bool Symbol_virtual_equals(Object *self, Object *obj);

bool Symbol_virtual_less(Object *self, Object *obj);

#ifdef __cplusplus
}
#endif
