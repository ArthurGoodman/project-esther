#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Function {
    Object base;

    struct std_string *name;
    Object *(*body)();
    int argc;
} Function;

Function *Function_new(Esther *esther, const char *name, Object *(*body)(), int argc);

void Function_init(Esther *esther, Function *self, const char *name, Object *(*body)(), int argc);

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args);

String *Function_virtual_toString(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
