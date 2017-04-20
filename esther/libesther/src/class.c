#include "esther/class.h"

#include "esther/esther.h"

struct Class *Class_new(struct Esther *esther) {
    UNUSED(esther);

    struct Class *volatile self = malloc(sizeof(struct Class));
    Class_init(esther, self);
    return self;
}

void Class_init(struct Esther *esther, struct Class *volatile self) {
    Object_init(esther, &self->object);
    self->methods = NULL;
}
