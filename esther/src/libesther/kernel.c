#include "kernel.h"

#include "esther.h"

static Object *ObjectClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Object_new(es);
}

static Object *ClassClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Class_new_anonymous(es);
}

static Object *StringClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    switch (Tuple_size(args)) {
    case 0:
        return String_new_c_str(es, "");

    case 1:
        return String_new(es, String_value(Object_toString(es, Tuple_get(args, 0))));

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }
}

static Object *SymbolClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return c_str_to_sym(es, "");
}

#define FunctionClass_virtual_newInstance Class_virtual_unimplemented_newInstance

static Object *TupleClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Tuple_new(es, 0);
}

static Object *ArrayClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Array_new(es, 0);
}

static Object *MapClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Map_new(es);
}

#define BooleanClass_virtual_newInstance Class_virtual_unimplemented_newInstance
#define NullClass_virtual_newInstance Class_virtual_unimplemented_newInstance
#define NumericClass_virtual_newInstance Class_virtual_unimplemented_newInstance

static Object *CharClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    switch (Tuple_size(args)) {
    case 0:
        return ValueObject_new_char(es, '\0');

    case 1: {
        Object *value = Tuple_get(args, 0);

        if (Object_getType(value) == TValueObject)
            return ValueObject_new_char(es, Variant_toChar(as_ValueObject(value)->value));
        else if (Object_getType(value) == TString)
            return ValueObject_new_char(es, String_c_str(value)[0]);
        else {
            Exception_throw_new(es, "invalid argument");
            return NULL;
        }
    }

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }
}

static Object *IntClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    switch (Tuple_size(args)) {
    case 0:
        return ValueObject_new_int(es, 0);

    case 1: {
        Object *value = Tuple_get(args, 0);

        if (Object_getType(value) == TValueObject)
            return ValueObject_new_int(es, Variant_toInt(as_ValueObject(value)->value));
        else if (Object_getType(value) == TString)
            return ValueObject_new_int(es, atoi(String_c_str(value)));
        else {
            Exception_throw_new(es, "invalid argument");
            return NULL;
        }
    }

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }
}

static Object *FloatClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    switch (Tuple_size(args)) {
    case 0:
        return ValueObject_new_real(es, 0.0);

    case 1: {
        Object *value = Tuple_get(args, 0);

        if (Object_getType(value) == TValueObject)
            return ValueObject_new_real(es, Variant_toReal(as_ValueObject(value)->value));
        else if (Object_getType(value) == TString)
            return ValueObject_new_real(es, atof(String_c_str(value)));
        else {
            Exception_throw_new(es, "invalid argument");
            return NULL;
        }
    }

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }
}

static Object *ExceptionClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    switch (Tuple_size(args)) {
    case 0:
        return Exception_new_error(es, string_const(""));

    case 1:
        return Exception_new_error(es, String_value(Tuple_get(args, 0)));

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }
}

static Object *RangeClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    int64_t start = 0;
    int64_t stop;
    int64_t step = 1;

    switch (Tuple_size(args)) {
    case 1:
        stop = Variant_toInt(ValueObject_getValue(Tuple_get(args, 0)));
        break;

    case 2:
        start = Variant_toInt(ValueObject_getValue(Tuple_get(args, 0)));
        stop = Variant_toInt(ValueObject_getValue(Tuple_get(args, 1)));
        break;

    case 3:
        start = Variant_toInt(ValueObject_getValue(Tuple_get(args, 0)));
        stop = Variant_toInt(ValueObject_getValue(Tuple_get(args, 1)));
        step = Variant_toInt(ValueObject_getValue(Tuple_get(args, 2)));
        break;

    default:
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }

    return Range_new(es, start, stop, step);
}

#define RangeIteratorClass_virtual_newInstance Class_virtual_unimplemented_newInstance

static Object *True_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new_c_str(es, "true");
}

static Object *False_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new_c_str(es, "false");
}

static bool False_virtual_isTrue(Object *UNUSED(self)) {
    return false;
}

static Object *Null_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new_c_str(es, "null");
}

static Object *ObjectClass_class(Esther *UNUSED(es), Object *self) {
    return Object_getClass(self);
}

static Object *ObjectClass_equals(Esther *es, Object *self, Object *obj) {
    return Esther_toBoolean(es, Object_equals(self, obj));
}

static Object *ObjectClass_clone(Esther *es, Object *self) {
    return Object_clone(es, self);
}

static Object *ClassClass_superclass(Esther *UNUSED(es), Object *self) {
    return Class_getSuperclass(self);
}

static Object *ClassClass_pars(Esther *es, Object *self, Object *args) {
    if (Tuple_size(args) != 2)
        Exception_throw_new(es, "invalid arguments");

    if (Object_getType(Tuple_get(args, 1)) != TTuple)
        Exception_throw_new(es, "invalid arguments");

    return Class_newInstance(es, self, Tuple_get(args, 1));
}

static Object *ClassClass_hasMethod(Esther *es, Object *self, Object *name) {
    return Esther_toBoolean(es, Class_hasMethod(self, str_to_id(String_value(name))));
}

static Object *ClassClass_getMethod(Esther *UNUSED(es), Object *self, Object *name) {
    return Class_getMethod(self, str_to_id(String_value(name)));
}

static Object *ClassClass_setMethod(Esther *UNUSED(es), Object *self, Object *name, Object *method) {
    Class_setMethod(self, str_to_id(String_value(name)), method);
    return method;
}

static Object *StringClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, String_size(self));
}

static Object *StringClass_capacity(Esther *es, Object *self) {
    return ValueObject_new_int(es, String_capacity(self));
}

static Object *StringClass_at(Esther *es, Object *self, Object *pos) {
    return ValueObject_new_char(es, String_c_str(self)[Variant_toInt(ValueObject_getValue(pos))]);
}

static Object *StringClass_plus(Esther *es, Object *self, Object *str) {
    return String_append(String_new(es, String_value(self)), Object_toString(es, str));
}

static Object *StringClass_append(Esther *es, Object *self, Object *str) {
    return String_append(self, Object_toString(es, str));
}

static Object *StringClass_contains(Esther *es, Object *self, Object *c) {
    return Esther_toBoolean(es, String_contains(self, Variant_toChar(ValueObject_getValue(c))));
}

static Object *TupleClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, Tuple_size(self));
}

static Object *TupleClass_at(Esther *UNUSED(es), Object *self, Object *index) {
    return Tuple_get(self, Variant_toInt(ValueObject_getValue(index)));
}

static Object *TupleClass_set(Esther *UNUSED(es), Object *self, Object *index, Object *value) {
    Tuple_set(self, Variant_toInt(ValueObject_getValue(index)), value);
    return value;
}

static Object *ArrayClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, Array_size(self));
}

static Object *ArrayClass_at(Esther *UNUSED(es), Object *self, Object *index) {
    return Array_get(self, Variant_toInt(ValueObject_getValue(index)));
}

static Object *ArrayClass_set(Esther *UNUSED(es), Object *self, Object *index, Object *value) {
    Array_set(self, Variant_toInt(ValueObject_getValue(index)), value);
    return value;
}

static Object *ArrayClass_push(Esther *UNUSED(es), Object *self, Object *value) {
    Array_push(self, value);
    return self;
}

static Object *ArrayClass_pop(Esther *UNUSED(es), Object *self) {
    return Array_pop(self);
}

static Object *MapClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, Map_size(self));
}

static Object *MapClass_contains(Esther *es, Object *self, Object *key) {
    return Esther_toBoolean(es, Map_contains(self, key));
}

static Object *MapClass_get(Esther *UNUSED(es), Object *self, Object *key) {
    return Map_get(self, key);
}

static Object *MapClass_set(Esther *UNUSED(es), Object *self, Object *key, Object *value) {
    Map_set(self, key, value);
    return value;
}

static Object *NumericClass_add(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_add(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_addAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_add(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_sub(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_sub(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_subAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_sub(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_mul(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_mul(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_mulAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_mul(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_div(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_div(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_divAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_div(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_mod(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_mod(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_modAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_mod(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_pow(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_pow(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_powAssign(Esther *UNUSED(es), Object *a, Object *b) {
    ValueObject_setValue(a, Variant_pow(ValueObject_getValue(a), ValueObject_getValue(b)));
    return a;
}

static Object *NumericClass_lt(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_lt(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_gt(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_gt(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_lte(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_lte(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_gte(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_gte(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_eq(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_eq(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_ne(Esther *es, Object *a, Object *b) {
    return Esther_toBoolean(es, Variant_ne(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_prefixDec(Esther *UNUSED(es), Object *self) {
    ValueObject_setValue(self, Variant_sub(ValueObject_getValue(self), Variant_int(1)));
    return self;
}

static Object *NumericClass_prefixInc(Esther *UNUSED(es), Object *self) {
    ValueObject_setValue(self, Variant_add(ValueObject_getValue(self), Variant_int(1)));
    return self;
}

static Object *NumericClass_suffixDec(Esther *es, Object *self) {
    Object *clone = Object_clone(es, self);
    ValueObject_setValue(self, Variant_sub(ValueObject_getValue(self), Variant_int(1)));
    return clone;
}

static Object *NumericClass_suffixInc(Esther *es, Object *self) {
    Object *clone = Object_clone(es, self);
    ValueObject_setValue(self, Variant_add(ValueObject_getValue(self), Variant_int(1)));
    return clone;
}

static Object *IntClass_range(Esther *es, Object *self, Object *arg) {
    int64_t start = Variant_toInt(ValueObject_getValue(self));
    int64_t stop = Variant_toInt(ValueObject_getValue(arg));
    int64_t step = start <= stop ? 1 : -1;

    return Range_new(es, start, stop, step);
}

static Object *CharClass_isSpace(Esther *es, Object *self) {
    return Esther_toBoolean(es, isspace(Variant_toChar(ValueObject_getValue(self))));
}

static Object *CharClass_isDigit(Esther *es, Object *self) {
    return Esther_toBoolean(es, isdigit(Variant_toChar(ValueObject_getValue(self))));
}

static Object *CharClass_isLetter(Esther *es, Object *self) {
    return Esther_toBoolean(es, isalpha(Variant_toChar(ValueObject_getValue(self))));
}

static Object *CharClass_isLetterOrDigit(Esther *es, Object *self) {
    return Esther_toBoolean(es, isalnum(Variant_toChar(ValueObject_getValue(self))));
}

static Object *ExceptionClass_throw(Esther *UNUSED(es), Object *self) {
    Exception_throw(self);
    return NULL;
}

CLASS_VTABLE(Class)
CLASS_VTABLE(Object)
CLASS_VTABLE(String)
CLASS_VTABLE(Symbol)
CLASS_VTABLE(Function)
CLASS_VTABLE(Tuple)
CLASS_VTABLE(Array)
CLASS_VTABLE(Map)
CLASS_VTABLE(Boolean)
CLASS_VTABLE(Null)
CLASS_VTABLE(Numeric)
CLASS_VTABLE(Char)
CLASS_VTABLE(Int)
CLASS_VTABLE(Float)
CLASS_VTABLE(Exception)
CLASS_VTABLE(Range)
CLASS_VTABLE(RangeIterator)

#define CONST_VTABLE(name, is_true)                      \
    static ObjectVTable vtable_for_##name = {            \
        .base = {                                        \
            .base = {                                    \
                .mapOnRefs = Object_virtual_mapOnRefs }, \
            .finalize = Object_virtual_finalize },       \
        .toString = name##_virtual_toString,             \
        .inspect = name##_virtual_toString,              \
        .equals = Object_virtual_equals,                 \
        .less = Object_virtual_less,                     \
        .isTrue = is_true##_virtual_isTrue,              \
        .clone = Object_virtual_clone_unimplemented      \
    };

CONST_VTABLE(True, Object)
CONST_VTABLE(False, False)
CONST_VTABLE(Null, False)

void Kernel_initialize(Esther *es) {
    Esther_setRootObject(es, c_str_to_id("Object"), NULL);
    Esther_setRootObject(es, c_str_to_id("Class"), NULL);

    Object *classClass = Class_new(es, string_const("Class"), NULL);
    classClass->objectClass = classClass;
    Esther_setRootObject(es, str_to_id(Class_getName(classClass)), classClass);
    *(void **) classClass = &vtable_for_ClassClass;

    Object *objectClass = Class_new(es, string_const("Object"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(objectClass)), objectClass);
    as_Class(classClass)->superclass = objectClass;
    *(void **) objectClass = &vtable_for_ObjectClass;

    Object *stringClass = Class_new(es, string_const("String"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(stringClass)), stringClass);
    *(void **) stringClass = &vtable_for_StringClass;

    Object *symbolClass = Class_new(es, string_const("Symbol"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(symbolClass)), symbolClass);
    *(void **) symbolClass = &vtable_for_SymbolClass;

    Object *functionClass = Class_new(es, string_const("Function"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(functionClass)), functionClass);
    *(void **) functionClass = &vtable_for_FunctionClass;

    Object *tupleClass = Class_new(es, string_const("Tuple"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(tupleClass)), tupleClass);
    *(void **) tupleClass = &vtable_for_TupleClass;

    Object *arrayClass = Class_new(es, string_const("Array"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(arrayClass)), arrayClass);
    *(void **) arrayClass = &vtable_for_ArrayClass;

    Object *mapClass = Class_new(es, string_const("Map"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(mapClass)), mapClass);
    *(void **) mapClass = &vtable_for_MapClass;

    Object *booleanClass = Class_new(es, string_const("Boolean"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(booleanClass)), booleanClass);
    *(void **) booleanClass = &vtable_for_BooleanClass;

    Object *nullClass = Class_new(es, string_const("Null"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(nullClass)), nullClass);
    *(void **) nullClass = &vtable_for_NullClass;

    Object *numericClass = Class_new(es, string_const("Numeric"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(numericClass)), numericClass);
    *(void **) numericClass = &vtable_for_NumericClass;

    Object *charClass = Class_new(es, string_const("Char"), numericClass);
    Esther_setRootObject(es, str_to_id(Class_getName(charClass)), charClass);
    *(void **) charClass = &vtable_for_CharClass;

    Object *intClass = Class_new(es, string_const("Int"), numericClass);
    Esther_setRootObject(es, str_to_id(Class_getName(intClass)), intClass);
    *(void **) intClass = &vtable_for_IntClass;

    Object *floatClass = Class_new(es, string_const("Float"), numericClass);
    Esther_setRootObject(es, str_to_id(Class_getName(floatClass)), floatClass);
    *(void **) floatClass = &vtable_for_FloatClass;

    Object *exceptionClass = Class_new(es, string_const("Exception"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(exceptionClass)), exceptionClass);
    *(void **) exceptionClass = &vtable_for_ExceptionClass;

    Object *rangeClass = Class_new(es, string_const("Range"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(rangeClass)), rangeClass);
    *(void **) rangeClass = &vtable_for_RangeClass;

    Object *rangeIteratorClass = Class_new(es, string_const("RangeIterator"), NULL);
    Esther_setRootObject(es, str_to_id(Class_getName(rangeIteratorClass)), rangeIteratorClass);
    *(void **) rangeIteratorClass = &vtable_for_RangeIteratorClass;

    es->trueObject = Object_new(es);
    es->trueObject->objectClass = booleanClass;
    *(void **) es->trueObject = &vtable_for_True;

    es->falseObject = Object_new(es);
    es->falseObject->objectClass = booleanClass;
    *(void **) es->falseObject = &vtable_for_False;

    es->nullObject = Object_new(es);
    es->nullObject->objectClass = nullClass;
    *(void **) es->nullObject = &vtable_for_Null;

    Class_setMethod_func(objectClass, Function_new(es, string_const("class"), (Object * (*) ()) ObjectClass_class, 0));
    Class_setMethod_func(objectClass, Function_new(es, string_const("toString"), (Object * (*) ()) Object_toString, 0));
    Class_setMethod_func(objectClass, Function_new(es, string_const("inspect"), (Object * (*) ()) Object_inspect, 0));
    Class_setMethod_func(objectClass, Function_new(es, string_const("equals"), (Object * (*) ()) ObjectClass_equals, 1));
    Class_setMethod_func(objectClass, Function_new(es, string_const("clone"), (Object * (*) ()) ObjectClass_clone, 0));
    Class_setMethod(objectClass, c_str_to_id("=="), Class_getMethod(objectClass, c_str_to_id("equals")));

    Class_setMethod_func(classClass, Function_new(es, string_const("superclass"), (Object * (*) ()) ClassClass_superclass, 0));
    Class_setMethod_func(classClass, Function_new(es, string_const("new"), (Object * (*) ()) Class_newInstance, -1));
    Class_setMethod_func(classClass, Function_new(es, string_const("()"), (Object * (*) ()) ClassClass_pars, -1));
    Class_setMethod_func(classClass, Function_new(es, string_const("hasMethod"), (Object * (*) ()) ClassClass_hasMethod, 1));
    Class_setMethod_func(classClass, Function_new(es, string_const("getMethod"), (Object * (*) ()) ClassClass_getMethod, 1));
    Class_setMethod_func(classClass, Function_new(es, string_const("setMethod"), (Object * (*) ()) ClassClass_setMethod, 2));

    Class_setMethod_func(stringClass, Function_new(es, string_const("size"), (Object * (*) ()) StringClass_size, 0));
    Class_setMethod_func(stringClass, Function_new(es, string_const("capacity"), (Object * (*) ()) StringClass_capacity, 0));
    Class_setMethod_func(stringClass, Function_new(es, string_const("at"), (Object * (*) ()) StringClass_at, 1));
    Class_setMethod(stringClass, c_str_to_id("[]"), Class_getMethod(stringClass, c_str_to_id("at")));
    Class_setMethod_func(stringClass, Function_new(es, string_const("+"), (Object * (*) ()) StringClass_plus, 1));
    Class_setMethod_func(stringClass, Function_new(es, string_const("append"), (Object * (*) ()) StringClass_append, 1));
    Class_setMethod(stringClass, c_str_to_id("+="), Class_getMethod(stringClass, c_str_to_id("append")));
    Class_setMethod_func(stringClass, Function_new(es, string_const("contains"), (Object * (*) ()) StringClass_contains, 1));

    Class_setMethod_func(functionClass, Function_new(es, string_const("call"), (Object * (*) ()) Function_invoke, 2));
    Class_setMethod(functionClass, c_str_to_id("()"), Class_getMethod(functionClass, c_str_to_id("call")));

    Class_setMethod_func(tupleClass, Function_new(es, string_const("size"), (Object * (*) ()) TupleClass_size, 0));
    Class_setMethod_func(tupleClass, Function_new(es, string_const("at"), (Object * (*) ()) TupleClass_at, 1));
    Class_setMethod(tupleClass, c_str_to_id("[]"), Class_getMethod(tupleClass, c_str_to_id("at")));
    Class_setMethod_func(tupleClass, Function_new(es, string_const("set"), (Object * (*) ()) TupleClass_set, 2));

    Class_setMethod_func(arrayClass, Function_new(es, string_const("size"), (Object * (*) ()) ArrayClass_size, 0));
    Class_setMethod_func(arrayClass, Function_new(es, string_const("at"), (Object * (*) ()) ArrayClass_at, 1));
    Class_setMethod(arrayClass, c_str_to_id("[]"), Class_getMethod(arrayClass, c_str_to_id("at")));
    Class_setMethod_func(arrayClass, Function_new(es, string_const("set"), (Object * (*) ()) ArrayClass_set, 2));
    Class_setMethod_func(arrayClass, Function_new(es, string_const("push"), (Object * (*) ()) ArrayClass_push, 1));
    Class_setMethod_func(arrayClass, Function_new(es, string_const("pop"), (Object * (*) ()) ArrayClass_pop, 0));

    Class_setMethod_func(mapClass, Function_new(es, string_const("size"), (Object * (*) ()) MapClass_size, 0));
    Class_setMethod_func(mapClass, Function_new(es, string_const("contains"), (Object * (*) ()) MapClass_contains, 1));
    Class_setMethod_func(mapClass, Function_new(es, string_const("get"), (Object * (*) ()) MapClass_get, 1));
    Class_setMethod(mapClass, c_str_to_id("[]"), Class_getMethod(mapClass, c_str_to_id("get")));
    Class_setMethod_func(mapClass, Function_new(es, string_const("set"), (Object * (*) ()) MapClass_set, 2));

    Class_setMethod_func(numericClass, Function_new(es, string_const("+"), (Object * (*) ()) NumericClass_add, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("+="), (Object * (*) ()) NumericClass_addAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("-"), (Object * (*) ()) NumericClass_sub, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("-="), (Object * (*) ()) NumericClass_subAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("*"), (Object * (*) ()) NumericClass_mul, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("*="), (Object * (*) ()) NumericClass_mulAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("/"), (Object * (*) ()) NumericClass_div, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("/="), (Object * (*) ()) NumericClass_divAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("%"), (Object * (*) ()) NumericClass_mod, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("%="), (Object * (*) ()) NumericClass_modAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("**"), (Object * (*) ()) NumericClass_pow, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("**="), (Object * (*) ()) NumericClass_powAssign, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("<"), (Object * (*) ()) NumericClass_lt, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const(">"), (Object * (*) ()) NumericClass_gt, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("<="), (Object * (*) ()) NumericClass_lte, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const(">="), (Object * (*) ()) NumericClass_gte, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("=="), (Object * (*) ()) NumericClass_eq, 1));
    Class_setMethod_func(numericClass, Function_new(es, string_const("!="), (Object * (*) ()) NumericClass_ne, 1));

    Class_setMethod_func(numericClass, Function_new(es, string_const("--_"), (Object * (*) ()) NumericClass_prefixDec, 0));
    Class_setMethod_func(numericClass, Function_new(es, string_const("++_"), (Object * (*) ()) NumericClass_prefixInc, 0));
    Class_setMethod_func(numericClass, Function_new(es, string_const("_--"), (Object * (*) ()) NumericClass_suffixDec, 0));
    Class_setMethod_func(numericClass, Function_new(es, string_const("_++"), (Object * (*) ()) NumericClass_suffixInc, 0));

    Class_setMethod_func(intClass, Function_new(es, string_const(".."), (Object * (*) ()) IntClass_range, 1));

    Class_setMethod_func(charClass, Function_new(es, string_const("isSpace"), (Object * (*) ()) CharClass_isSpace, 0));
    Class_setMethod_func(charClass, Function_new(es, string_const("isDigit"), (Object * (*) ()) CharClass_isDigit, 0));
    Class_setMethod_func(charClass, Function_new(es, string_const("isLetter"), (Object * (*) ()) CharClass_isLetter, 0));
    Class_setMethod_func(charClass, Function_new(es, string_const("isLetterOrDigit"), (Object * (*) ()) CharClass_isLetterOrDigit, 0));

    Class_setMethod_func(exceptionClass, Function_new(es, string_const("throw"), (Object * (*) ()) ExceptionClass_throw, 0));

    Class_setMethod_func(rangeClass, Function_new(es, string_const("start"), (Object * (*) ()) Range_getStart, 0));
    Class_setMethod_func(rangeClass, Function_new(es, string_const("stop"), (Object * (*) ()) Range_getStop, 0));
    Class_setMethod_func(rangeClass, Function_new(es, string_const("step"), (Object * (*) ()) Range_getStep, 0));
    Class_setMethod_func(rangeClass, Function_new(es, string_const("iterator"), (Object * (*) ()) Range_iterator, 0));

    Class_setMethod_func(rangeIteratorClass, Function_new(es, string_const("next"), (Object * (*) ()) RangeIterator_next, 0));
}
