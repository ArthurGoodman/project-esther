#include "esther/esther.h"

#include "esther/class.h"
#include "esther/object.h"

struct Esther *Esther_new() {
    struct Esther *self = malloc(sizeof(struct Esther));

    self->classClass = Class_new(self, "Class", NULL);
    self->classClass->base.objectClass = self->classClass;

    self->objectClass = Class_new(self, "Object", NULL);
    self->classClass->superclass = self->objectClass;

    self->functionClass = Class_new(self, "Function", self->classClass);

    self->mainObject = Object_new(self);
    self->trueObject = NULL;
    self->falseObject = NULL;

    return self;
}
