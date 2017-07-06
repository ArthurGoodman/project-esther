#include "esther/esther.h"

#include "esther/common.h"
#include "esther/memory.h"
#include "esther/utility.h"

void Esther_init(Esther *es) {
    uint8_t local;
    gc_initialize((ptr_ptr_t) &local);

    es->objectClass = NULL;
    es->classClass = NULL;
    es->stringClass = NULL;
    es->symbolClass = NULL;
    es->functionClass = NULL;
    es->tupleClass = NULL;
    es->arrayClass = NULL;
    es->booleanClass = NULL;
    es->nullClass = NULL;
    es->numericClass = NULL;
    es->charClass = NULL;
    es->intClass = NULL;
    es->floatClass = NULL;
    es->exceptionClass = NULL;

    es->trueObject = NULL;
    es->falseObject = NULL;
    es->nullObject = NULL;

    es->mainObject = NULL;
    es->esther = NULL;

    es->root = NULL;
}

void Esther_finalize(Esther *es) {
}

bool Esther_hasRootObject(Esther *es, struct string name) {
}

Object *Esther_getRootObject(Esther *es, struct string name) {
}

void Esther_setRootObject(Esther *es, struct string name, Object *value) {
}

void Esther_runFile(Esther *es, const char *fileName) {
}

Object *Esther_eval(Esther *es, Object *ast, Context *context) {
}
