#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Context Context;

typedef struct Function {
    Object base;

    const char *name;
    Object *(*body)();
    int argc;
} Function;

Function *Function_new(Esther *esther, const char *name, Object *(*body)(), int argc);

void Function_init(Esther *esther, Function *self, const char *name, Object *(*body)(), int argc);

const char *Function_getName(Function *self);

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args);

String *Function_virtual_toString(Esther *esther, Object *self);

typedef struct InterpretedFunction {
    Function base;

    const char **params;
    Context *closure;
    Object *body;
} InterpretedFunction;

Function *InterpretedFunction_new(Esther *esther, const char *name, int argc, const char **params, Context *closure, Object *body);

#ifdef __cplusplus
}
#endif
