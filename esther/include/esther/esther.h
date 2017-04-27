#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"

typedef struct Context Context;

typedef struct Esther {
    Object *objectClass;
    Object *classClass;
    Object *stringClass;
    Object *symbolClass;
    Object *functionClass;
    Object *tupleClass;
    Object *arrayClass;
    Object *booleanClass;
    Object *nullClass;
    Object *numericClass;
    Object *charClass;
    Object *intClass;
    Object *floatClass;
    Object *exceptionClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    Object *lexer;
    Object *parser;

    Object *mainObject;
    Object *io;

    Context *root;

    struct std_map *rootObjects;
} Esther;

void Esther_init(Esther *es);

Object *Esther_toBoolean(Esther *es, bool value);

bool Esther_hasRootObject(Esther *es, const char *name);
Object *Esther_getRootObject(Esther *es, const char *name);
void Esther_setRootObject(Esther *es, const char *name, Object *value);

Object *Esther_eval(Esther *es, Object *ast, Context *context);

#ifdef __cplusplus
}
#endif
