#include "esther/class.h"

#include "esther/esther.h"
#include "str.h"

struct Class *Class_new(struct Esther *esther, const char *name, struct Class *volatile superclass) {
    struct Class *volatile self = malloc(sizeof(struct Class));
    Class_init(esther, self, name, superclass);
    return self;
}

void Class_init(struct Esther *esther, struct Class *volatile self, const char *name, struct Class *volatile superclass) {
    self->base.objectClass = esther->classClass;
    self->base.attributes = NULL;
    self->name = string_new_c_str(name);
    self->superclass = superclass;
    self->methods = NULL;
}
