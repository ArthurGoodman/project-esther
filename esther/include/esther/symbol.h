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

Symbol *Symbol_new(Esther *esther, const char *name);

void Symbol_init(Esther *esther, Symbol *symbol, const char *name);

String *Symbol_virtual_toString(Esther *esther, Object *self);
String *Symbol_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
