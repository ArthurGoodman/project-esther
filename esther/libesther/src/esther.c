#include "esther/esther.h"

#include "esther/class.h"
#include "esther/object.h"

void Esther_init(struct Esther *self) {
    self->classClass = Class_new_init(self, "Class", NULL);
    self->classClass->base.objectClass = self->classClass;

    self->objectClass = NULL;
    self->objectClass = Class_new_init(self, "Object", NULL);
    self->classClass->superclass = self->objectClass;

    self->stringClass = Class_new_init(self, "String", NULL);

    self->functionClass = Class_new_init(self, "Function", NULL);

    self->mainObject = Object_new(self);
    self->trueObject = NULL;
    self->falseObject = NULL;
}
