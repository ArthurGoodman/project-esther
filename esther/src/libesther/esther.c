#include "esther/esther.h"

#include "esther/class.h"
#include "esther/object.h"
#include "esther/string.h"

static Object *ClassClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)Class_new(esther);
}

static Object *StringClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)String_new(esther);
}

void Esther_init(Esther *self) {
    self->classClass = Class_new_init(self, "Class", NULL);
    self->classClass->base.objectClass = self->classClass;
    self->classClass->newInstance = ClassClass_virtual_newInstance;

    self->objectClass = NULL;
    self->objectClass = Class_new_init(self, "Object", NULL);
    self->classClass->superclass = self->objectClass;

    self->stringClass = Class_new_init(self, "String", NULL);
    self->stringClass->newInstance = StringClass_virtual_newInstance;

    self->functionClass = Class_new_init(self, "Function", NULL);

    self->mainObject = Object_new(self);
    self->trueObject = NULL;
    self->falseObject = NULL;
}
