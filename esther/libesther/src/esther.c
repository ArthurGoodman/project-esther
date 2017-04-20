#include "esther/esther.h"

struct Esther *Esther_new() {
    struct Esther *esther = malloc(sizeof(struct Esther));

    esther->objectClass = NULL;
    esther->classClass = NULL;

    esther->mainObject = NULL;
    esther->trueObject = NULL;
    esther->falseObject = NULL;

    return esther;
}
