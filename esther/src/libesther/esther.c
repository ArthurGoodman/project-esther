#include "esther/esther.h"

#include "esther/class.h"
#include "esther/object.h"
#include "esther/string.h"
#include "esther/tuple.h"
#include "esther/array.h"

static Object *ObjectClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return Object_new(esther);
}

static Object *ClassClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)Class_new(esther);
}

static Object *StringClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)String_new(esther);
}

static Object *FunctionClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(esther);
    UNUSED(self);
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)Tuple_new(esther);
}

static Object *ArrayClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(self);
    return (Object *)Array_new(esther);
}

static Object *BooleanClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(esther);
    UNUSED(self);
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *esther, Class *self) {
    UNUSED(esther);
    UNUSED(self);
    return NULL;
}

static String *True_toString(Esther *esther, Object *self) {
    UNUSED(self);
    return String_new_init(esther, "true");
}

static String *False_toString(Esther *esther, Object *self) {
    UNUSED(self);
    return String_new_init(esther, "false");
}

static String *Null_toString(Esther *esther, Object *self) {
    UNUSED(self);
    return String_new_init(esther, "null");
}

void Esther_init(Esther *self) {
    self->classClass = Class_new_init(self, "Class", NULL);
    self->classClass->base.objectClass = self->classClass;
    self->classClass->newInstance = ClassClass_virtual_newInstance;

    self->objectClass = NULL;
    self->objectClass = Class_new_init(self, "Object", NULL);
    self->classClass->superclass = self->objectClass;
    self->objectClass->newInstance = ObjectClass_virtual_newInstance;

    self->stringClass = Class_new_init(self, "String", NULL);
    self->stringClass->newInstance = StringClass_virtual_newInstance;

    self->functionClass = Class_new_init(self, "Function", NULL);
    self->functionClass->newInstance = FunctionClass_virtual_newInstance;

    self->tupleClass = Class_new_init(self, "Tuple", NULL);
    self->tupleClass->newInstance = TupleClass_virtual_newInstance;

    self->arrayClass = Class_new_init(self, "Array", NULL);
    self->arrayClass->newInstance = ArrayClass_virtual_newInstance;

    self->booleanClass = Class_new_init(self, "Boolean", NULL);
    self->booleanClass->newInstance = BooleanClass_virtual_newInstance;

    self->nullClass = Class_new_init(self, "Null", NULL);
    self->nullClass->newInstance = NullClass_virtual_newInstance;

    self->trueObject = Object_new(self);
    self->trueObject->objectClass = self->booleanClass;
    self->trueObject->toString = self->trueObject->inspect = True_toString;

    self->falseObject = Object_new(self);
    self->falseObject->objectClass = self->booleanClass;
    self->falseObject->toString = self->falseObject->inspect = False_toString;

    self->nullObject = Object_new(self);
    self->nullObject->objectClass = self->nullClass;
    self->nullObject->toString = self->nullObject->inspect = Null_toString;

    self->mainObject = Object_new(self);
}
