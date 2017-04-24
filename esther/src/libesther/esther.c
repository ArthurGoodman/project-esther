#include "esther/esther.h"

#include "esther/array.h"
#include "esther/class.h"
#include "esther/function.h"
#include "esther/object.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/valueobject.h"

static Object *ObjectClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return Object_new(esther);
}

static Object *ClassClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)Class_new(esther);
}

static Object *StringClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)String_new(esther);
}

static Object *SymbolClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)Symbol_new(esther, "");
}

static Object *FunctionClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self)) {
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)Tuple_new(esther);
}

static Object *ArrayClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)Array_new(esther);
}

static Object *BooleanClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self)) {
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self)) {
    return NULL;
}

static Object *NumericClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self)) {
    return NULL;
}

static Object *CharClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)ValueObject_new_char(esther, '\0');
}

static Object *IntClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)ValueObject_new_int(esther, 0);
}

static Object *FloatClass_virtual_newInstance(Esther *esther, Class *UNUSED(self)) {
    return (Object *)ValueObject_new_real(esther, 0.0);
}

static String *True_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new_init(esther, "true");
}

static String *False_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new_init(esther, "false");
}

static String *Null_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new_init(esther, "null");
}

Object *Numeric_add(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_add(a->value, b->value));
}

Object *Numeric_sub(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_sub(a->value, b->value));
}

Object *Numeric_mul(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_mul(a->value, b->value));
}

Object *Numeric_div(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_div(a->value, b->value));
}

Object *Numeric_mod(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_mod(a->value, b->value));
}

Object *Numeric_pow(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_pow(a->value, b->value));
}

Object *Numeric_lt(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_lt(a->value, b->value));
}

Object *Numeric_gt(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_gt(a->value, b->value));
}

Object *Numeric_lte(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_lte(a->value, b->value));
}

Object *Numeric_gte(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_gte(a->value, b->value));
}

Object *Numeric_eq(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_eq(a->value, b->value));
}

Object *Numeric_ne(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_ne(a->value, b->value));
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

    self->symbolClass = Class_new_init(self, "Symbol", NULL);
    self->symbolClass->newInstance = SymbolClass_virtual_newInstance;

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

    self->numericClass = Class_new_init(self, "Numeric", NULL);
    self->numericClass->newInstance = NumericClass_virtual_newInstance;

    Class_setMethod_func(self->numericClass, Function_new(self, "+", (Object * (*)())Numeric_add, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "-", (Object * (*)())Numeric_sub, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "*", (Object * (*)())Numeric_mul, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "/", (Object * (*)())Numeric_div, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "%", (Object * (*)())Numeric_mod, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "^", (Object * (*)())Numeric_pow, 1));

    Class_setMethod_func(self->numericClass, Function_new(self, "<", (Object * (*)())Numeric_lt, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, ">", (Object * (*)())Numeric_gt, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "<=", (Object * (*)())Numeric_lte, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, ">=", (Object * (*)())Numeric_gte, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "==", (Object * (*)())Numeric_eq, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "!=", (Object * (*)())Numeric_ne, 1));

    self->charClass = Class_new_init(self, "Char", self->numericClass);
    self->charClass->newInstance = CharClass_virtual_newInstance;

    self->intClass = Class_new_init(self, "Int", self->numericClass);
    self->intClass->newInstance = IntClass_virtual_newInstance;

    Class_setMethod(self->intClass, "+", (Object *)Function_new(self, "+", (Object * (*)())Numeric_add, 1));

    self->floatClass = Class_new_init(self, "Float", self->numericClass);
    self->floatClass->newInstance = FloatClass_virtual_newInstance;

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

Object *Esther_toBoolean(Esther *self, bool value) {
    return value ? self->trueObject : self->falseObject;
}
