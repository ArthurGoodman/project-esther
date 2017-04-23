#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Function {
    Object base;

    Object *(*body)();
    int argc;
} Function;

Function *Function_new(Esther *esther, Object *(*body)(), int argc);

void Function_init(Esther *esther, Function *self, Object *(*body)(), int argc);

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args);

#ifdef __cplusplus
}
#endif
