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

#define as_Function(obj) ((Function *)(obj))

Object *Function_new(Esther *es, const char *name, Object *(*body)(), int argc);

void Function_init(Esther *es, Object *self, const char *name, Object *(*body)(), int argc);

const char *Function_getName(Object *self);

Object *Function_invoke(Esther *es, Object *self, Object *selfObject, Object *args);

Object *Function_virtual_toString(Esther *es, Object *self);

typedef struct InterpretedFunction {
    Function base;

    int argc;
    const char **params;
    Context *closure;
    Object *body;
} InterpretedFunction;

#define as_InterpretedFunction(obj) ((InterpretedFunction *)(obj))

Object *InterpretedFunction_new(Esther *es, const char *name, Object *params, Context *closure, Object *body);

void InterpretedFunction_init(Esther *es, Object *self, const char *name, Object *params, Context *closure, Object *body);

#ifdef __cplusplus
}
#endif
