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

#define as_function(obj) ((Function *)(obj))

Object *Function_new(Esther *esther, const char *name, Object *(*body)(), int argc);

void Function_init(Esther *esther, Object *self, const char *name, Object *(*body)(), int argc);

const char *Function_getName(Object *self);

Object *Function_invoke(Esther *esther, Object *self, Object *selfObject, Object *args);

Object *Function_virtual_toString(Esther *esther, Object *self);

typedef struct InterpretedFunction {
    Function base;

    const char **params;
    Context *closure;
    Object *body;
} InterpretedFunction;

#define as_interpretedFunction(obj) ((InterpretedFunction *)(obj))

Object *InterpretedFunction_new(Esther *esther, const char *name, int argc, const char **params, Context *closure, Object *body);

#ifdef __cplusplus
}
#endif
