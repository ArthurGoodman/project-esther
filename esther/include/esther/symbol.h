#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/id.h"
#include "esther/object.h"

typedef struct Symbol {
    Object base;

    Id id;
} Symbol;

#define as_symbol(obj) ((Symbol *)(obj))

Object *Symbol_new(Esther *esther, const char *name);

void Symbol_init(Esther *esther, Object *symbol, const char *name);

Id Symbol_getId(Object *self);

Object *Symbol_virtual_toString(Esther *esther, Object *self);
Object *Symbol_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
