#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"
#include "esther/std_string.h"

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

    Object *mainObject;
    Object *esther;

    Context *root;

    struct std_map *rootObjects;
} Esther;

void Esther_init(Esther *es);
void Esther_finalize(Esther *es);

bool Esther_hasRootObject(Esther *es, struct string name);
Object *Esther_getRootObject(Esther *es, struct string name);
void Esther_setRootObject(Esther *es, struct string name, Object *value);

void Esther_runFile(Esther *es, const char *fileName);

Object *Esther_eval(Esther *es, Object *ast, Context *context);

#ifdef __cplusplus
}
#endif
