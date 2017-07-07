#include "esther/esther.h"

#include "esther/array.h"
#include "esther/class.h"
#include "esther/context.h"
#include "esther/exception.h"
#include "esther/function.h"
#include "esther/lexer.h"
#include "esther/memory.h"
#include "esther/object.h"
#include "esther/parser.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/utility.h"
#include "esther/valueobject.h"
#include "identifiers.h"

static Object *ObjectClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Object_new(es);
}

static Object *ClassClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Class_new(es);
}

static Object *StringClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return String_new_c_str(es, "");
}

static Object *SymbolClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Symbol_new_c_str(es, "");
}

static Object *FunctionClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw_new(es, "cannot create an instance of Function class yet...");
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Tuple_new(es, 0);
}

static Object *ArrayClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Array_new(es, 0);
}

static Object *BooleanClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw_new(es, "cannot create an instance of Boolean class");
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw_new(es, "cannot create an instance of Null class");
    return NULL;
}

static Object *NumericClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw_new(es, "cannot create an instance of Numeric class");
    return NULL;
}

static Object *CharClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_char(es, '\0');

    if (Tuple_size(args) == 1) {
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

    Exception_throw_new(es, "invalid number of arguments");
    return NULL;
}

static Object *IntClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_int(es, 0);

    if (Tuple_size(args) == 1) {
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

    Exception_throw_new(es, "invalid number of arguments");
    return NULL;
}

static Object *FloatClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_real(es, '\0');

    if (Tuple_size(args) == 1) {
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

    Exception_throw_new(es, "invalid number of arguments");
    return NULL;
}

static Object *ExceptionClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Exception_new(es, string_const(""));
}

static Object *True_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new_c_str(es, "true");
}

static Object *False_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new_c_str(es, "false");
}

static bool False_virtual_isTrue() {
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
    return Esther_toBoolean(es, Class_hasMethod(self, String_value(name)));
}

static Object *ClassClass_getMethod(Esther *UNUSED(es), Object *self, Object *name) {
    return Class_getMethod(self, String_value(name));
}

static Object *ClassClass_setMethod(Esther *UNUSED(es), Object *self, Object *name, Object *method) {
    Class_setMethod(self, String_value(name), method);
    return method;
}

static Object *StringClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, String_size(self));
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

static Object *IO_write(Esther *es, Object *self, Object *args) {
    if (Tuple_size(args) == 0)
        printf("%s", String_c_str(Object_toString(es, self)));
    else
        for (size_t i = 0; i < Tuple_size(args); i++)
            printf("%s", String_c_str(Object_toString(es, Tuple_get(args, i))));

    return es->nullObject;
}

static Object *IO_writeLine(Esther *es, Object *self, Object *args) {
    if (Tuple_size(args) == 0)
        printf("%s\n", String_c_str(Object_toString(es, self)));
    else
        for (size_t i = 0; i < Tuple_size(args); i++)
            printf("%s\n", String_c_str(Object_toString(es, Tuple_get(args, i))));

    return es->nullObject;
}

static Object *Esther_evalFunction(Esther *es, Object *UNUSED(self), Object *ast) {
    return Esther_eval(es, ast, es->root);
}

typedef struct GlobalMapper {
    Mapper base;

    Esther *es;
} GlobalMapper;

static void GlobalMapper_mapOnRefs(GlobalMapper *self, MapFunction f) {
    f(self->es->objectClass);
    f(self->es->classClass);
    f(self->es->stringClass);
    f(self->es->symbolClass);
    f(self->es->functionClass);
    f(self->es->tupleClass);
    f(self->es->arrayClass);
    f(self->es->booleanClass);
    f(self->es->nullClass);
    f(self->es->numericClass);
    f(self->es->charClass);
    f(self->es->intClass);
    f(self->es->floatClass);
    f(self->es->exceptionClass);

    f(self->es->trueObject);
    f(self->es->falseObject);
    f(self->es->nullObject);

    f(self->es->lexer);
    f(self->es->parser);

    f(self->es->mainObject);
    f(self->es->esther);
    f(self->es->io);

    f(self->es->root);

#define X(a, b) f(sym_##a);
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X

    for (struct FileRecord *rec = self->es->file; rec; rec = rec->next)
        f(rec->source);
}

static VTableForMapper GlobalMapper_vtable = {
    .mapOnRefs = (void (*)(Mapper *, MapFunction)) GlobalMapper_mapOnRefs
};

static Mapper *GlobalMapper_new(Esther *es) {
    GlobalMapper *self = malloc(sizeof(GlobalMapper));
    self->es = es;
    *(void **) self = &GlobalMapper_vtable;
    return (Mapper *) self;
}

#define CLASS_VTABLE(name)                                  \
    static VTableForClass name##Class_vtable = {            \
        .base = {                                           \
            .base = {                                       \
                .base = {                                   \
                    .mapOnRefs = Class_virtual_mapOnRefs }, \
                .finalize = Class_virtual_finalize },       \
            .toString = Class_virtual_toString,             \
            .inspect = Class_virtual_toString,              \
            .equals = Object_virtual_equals,                \
            .isTrue = Object_virtual_isTrue },              \
        .newInstance = name##Class_virtual_newInstance      \
    };

CLASS_VTABLE(Class)
CLASS_VTABLE(Object)
CLASS_VTABLE(String)
CLASS_VTABLE(Symbol)
CLASS_VTABLE(Function)
CLASS_VTABLE(Tuple)
CLASS_VTABLE(Array)
CLASS_VTABLE(Boolean)
CLASS_VTABLE(Null)
CLASS_VTABLE(Numeric)
CLASS_VTABLE(Char)
CLASS_VTABLE(Int)
CLASS_VTABLE(Float)
CLASS_VTABLE(Exception)

#define CONST_VTABLE(name, is_true)                      \
    static VTableForObject name##_vtable = {             \
        .base = {                                        \
            .base = {                                    \
                .mapOnRefs = Object_virtual_mapOnRefs }, \
            .finalize = Object_virtual_finalize },       \
        .toString = name##_virtual_toString,             \
        .inspect = name##_virtual_toString,              \
        .equals = Object_virtual_equals,                 \
        .isTrue = is_true##_virtual_isTrue               \
    };

CONST_VTABLE(True, Object)
CONST_VTABLE(False, False)
CONST_VTABLE(Null, False)

void Esther_init(Esther *es) {
    gc_registerMapper(GlobalMapper_new(es));

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

    es->lexer = NULL;
    es->parser = NULL;

    es->mainObject = NULL;
    es->esther = NULL;
    es->io = NULL;

    es->root = NULL;

    es->file = NULL;

    es->classClass = Class_new_init(es, string_const("Class"), NULL);
    as_Class(es->classClass)->base.objectClass = es->classClass;
    *(void **) es->classClass = &ClassClass_vtable;

    es->objectClass = NULL;
    es->objectClass = Class_new_init(es, string_const("Object"), NULL);
    as_Class(es->classClass)->superclass = es->objectClass;
    *(void **) es->objectClass = &ObjectClass_vtable;

    es->stringClass = Class_new_init(es, string_const("String"), NULL);
    *(void **) es->stringClass = &StringClass_vtable;

    es->symbolClass = Class_new_init(es, string_const("Symbol"), NULL);
    *(void **) es->symbolClass = &SymbolClass_vtable;

    es->functionClass = Class_new_init(es, string_const("Function"), NULL);
    *(void **) es->functionClass = &FunctionClass_vtable;

    es->tupleClass = Class_new_init(es, string_const("Tuple"), NULL);
    *(void **) es->tupleClass = &TupleClass_vtable;

    es->arrayClass = Class_new_init(es, string_const("Array"), NULL);
    *(void **) es->arrayClass = &ArrayClass_vtable;

    es->booleanClass = Class_new_init(es, string_const("Boolean"), NULL);
    *(void **) es->booleanClass = &BooleanClass_vtable;

    es->nullClass = Class_new_init(es, string_const("Null"), NULL);
    *(void **) es->nullClass = &NullClass_vtable;

    es->numericClass = Class_new_init(es, string_const("Numeric"), NULL);
    *(void **) es->numericClass = &NumericClass_vtable;

    es->charClass = Class_new_init(es, string_const("Char"), es->numericClass);
    *(void **) es->charClass = &CharClass_vtable;

    es->intClass = Class_new_init(es, string_const("Int"), es->numericClass);
    *(void **) es->intClass = &IntClass_vtable;

    es->floatClass = Class_new_init(es, string_const("Float"), es->numericClass);
    *(void **) es->floatClass = &FloatClass_vtable;

    es->exceptionClass = Class_new_init(es, string_const("Exception"), NULL);
    *(void **) es->exceptionClass = &ExceptionClass_vtable;

    es->trueObject = Object_new(es);
    es->trueObject->objectClass = es->booleanClass;
    *(void **) es->trueObject = &True_vtable;

    es->falseObject = Object_new(es);
    es->falseObject->objectClass = es->booleanClass;
    *(void **) es->falseObject = &False_vtable;

    es->nullObject = Object_new(es);
    es->nullObject->objectClass = es->nullClass;
    *(void **) es->nullObject = &Null_vtable;

    Class_setMethod_func(es->objectClass, Function_new(es, string_const("class"), (Object * (*) ()) ObjectClass_class, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, string_const("toString"), (Object * (*) ()) Object_toString, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, string_const("inspect"), (Object * (*) ()) Object_inspect, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, string_const("equals"), (Object * (*) ()) ObjectClass_equals, 1));
    Class_setMethod(es->objectClass, string_const("=="), Class_getMethod(es->objectClass, string_const("equals")));

    Class_setMethod_func(es->classClass, Function_new(es, string_const("superclass"), (Object * (*) ()) ClassClass_superclass, 0));
    Class_setMethod_func(es->classClass, Function_new(es, string_const("new"), (Object * (*) ()) Class_newInstance, -1));
    Class_setMethod_func(es->classClass, Function_new(es, string_const("()"), (Object * (*) ()) ClassClass_pars, -1));
    Class_setMethod_func(es->classClass, Function_new(es, string_const("hasMethod"), (Object * (*) ()) ClassClass_hasMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, string_const("getMethod"), (Object * (*) ()) ClassClass_getMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, string_const("setMethod"), (Object * (*) ()) ClassClass_setMethod, 2));

    Class_setMethod_func(es->stringClass, Function_new(es, string_const("size"), (Object * (*) ()) StringClass_size, 0));
    Class_setMethod_func(es->stringClass, Function_new(es, string_const("at"), (Object * (*) ()) StringClass_at, 1));
    Class_setMethod(es->stringClass, string_const("[]"), Class_getMethod(es->stringClass, string_const("at")));
    Class_setMethod_func(es->stringClass, Function_new(es, string_const("+"), (Object * (*) ()) StringClass_plus, 1));
    Class_setMethod_func(es->stringClass, Function_new(es, string_const("append"), (Object * (*) ()) StringClass_append, 1));
    Class_setMethod(es->stringClass, string_const("+="), Class_getMethod(es->stringClass, string_const("append")));
    Class_setMethod_func(es->stringClass, Function_new(es, string_const("contains"), (Object * (*) ()) StringClass_contains, 1));

    Class_setMethod_func(es->functionClass, Function_new(es, string_const("call"), (Object * (*) ()) Function_invoke, 2));
    Class_setMethod(es->functionClass, string_const("()"), Class_getMethod(es->functionClass, string_const("call")));

    Class_setMethod_func(es->tupleClass, Function_new(es, string_const("size"), (Object * (*) ()) TupleClass_size, 0));
    Class_setMethod_func(es->tupleClass, Function_new(es, string_const("at"), (Object * (*) ()) TupleClass_at, 1));
    Class_setMethod(es->tupleClass, string_const("[]"), Class_getMethod(es->tupleClass, string_const("at")));
    Class_setMethod_func(es->tupleClass, Function_new(es, string_const("set"), (Object * (*) ()) TupleClass_set, 2));

    Class_setMethod_func(es->arrayClass, Function_new(es, string_const("size"), (Object * (*) ()) ArrayClass_size, 0));
    Class_setMethod_func(es->arrayClass, Function_new(es, string_const("at"), (Object * (*) ()) ArrayClass_at, 1));
    Class_setMethod(es->arrayClass, string_const("[]"), Class_getMethod(es->arrayClass, string_const("at")));
    Class_setMethod_func(es->arrayClass, Function_new(es, string_const("set"), (Object * (*) ()) ArrayClass_set, 2));

    Class_setMethod_func(es->numericClass, Function_new(es, string_const("+"), (Object * (*) ()) NumericClass_add, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("+="), (Object * (*) ()) NumericClass_addAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("-"), (Object * (*) ()) NumericClass_sub, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("-="), (Object * (*) ()) NumericClass_subAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("*"), (Object * (*) ()) NumericClass_mul, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("*="), (Object * (*) ()) NumericClass_mulAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("/"), (Object * (*) ()) NumericClass_div, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("/="), (Object * (*) ()) NumericClass_divAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("%"), (Object * (*) ()) NumericClass_mod, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("%="), (Object * (*) ()) NumericClass_modAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("**"), (Object * (*) ()) NumericClass_pow, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("**="), (Object * (*) ()) NumericClass_powAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("<"), (Object * (*) ()) NumericClass_lt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const(">"), (Object * (*) ()) NumericClass_gt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("<="), (Object * (*) ()) NumericClass_lte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const(">="), (Object * (*) ()) NumericClass_gte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("=="), (Object * (*) ()) NumericClass_eq, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, string_const("!="), (Object * (*) ()) NumericClass_ne, 1));

    Class_setMethod_func(es->charClass, Function_new(es, string_const("isSpace"), (Object * (*) ()) CharClass_isSpace, 0));
    Class_setMethod_func(es->charClass, Function_new(es, string_const("isDigit"), (Object * (*) ()) CharClass_isDigit, 0));
    Class_setMethod_func(es->charClass, Function_new(es, string_const("isLetter"), (Object * (*) ()) CharClass_isLetter, 0));
    Class_setMethod_func(es->charClass, Function_new(es, string_const("isLetterOrDigit"), (Object * (*) ()) CharClass_isLetterOrDigit, 0));

    es->lexer = Lexer_new(es);

    Object_setAttribute(es->lexer, string_const("lex"), Function_new(es, string_const("lex"), (Object * (*) ()) Lexer_lex, 1));

    es->parser = Parser_new(es);

    Object_setAttribute(es->parser, string_const("parse"), Function_new(es, string_const("parse"), (Object * (*) ()) Parser_parse, 1));

    es->mainObject = Object_new(es);

    es->esther = Object_new(es);

    Object_setAttribute(es->esther, string_const("lexer"), es->lexer);
    Object_setAttribute(es->esther, string_const("parser"), es->parser);
    Object_setAttribute(es->esther, string_const("eval"), Function_new(es, string_const("eval"), (Object * (*) ()) Esther_evalFunction, 1));

    es->io = Object_new(es);

    Object_setAttribute(es->io, string_const("write"), Function_new(es, string_const("write"), (Object * (*) ()) IO_write, -1));
    Object_setAttribute(es->io, string_const("writeLine"), Function_new(es, string_const("writeLine"), (Object * (*) ()) IO_writeLine, -1));

    es->root = Context_new(es);

    es->rootObjects = std_map_new(compare_str);

    Esther_setRootObject(es, string_const("Object"), es->objectClass);
    Esther_setRootObject(es, string_const("Class"), es->classClass);
    Esther_setRootObject(es, string_const("String"), es->stringClass);
    Esther_setRootObject(es, string_const("Symbol"), es->symbolClass);
    Esther_setRootObject(es, string_const("Function"), es->functionClass);
    Esther_setRootObject(es, string_const("Tuple"), es->tupleClass);
    Esther_setRootObject(es, string_const("Array"), es->arrayClass);
    Esther_setRootObject(es, string_const("Boolean"), es->booleanClass);
    Esther_setRootObject(es, string_const("Null"), es->nullClass);
    Esther_setRootObject(es, string_const("Numeric"), es->numericClass);
    Esther_setRootObject(es, string_const("Char"), es->charClass);
    Esther_setRootObject(es, string_const("Int"), es->intClass);
    Esther_setRootObject(es, string_const("Float"), es->floatClass);

    Esther_setRootObject(es, string_const("IO"), es->io);
    Esther_setRootObject(es, string_const("esther"), es->esther);

    init_identifiers(es);
}

void Esther_finalize(Esther *UNUSED(es)) {
}

Object *Esther_toBoolean(Esther *es, bool value) {
    return value ? es->trueObject : es->falseObject;
}

bool Esther_hasRootObject(Esther *es, const struct string name) {
    return std_map_contains(es->rootObjects, &name);
}

Object *Esther_getRootObject(Esther *es, const struct string name) {
    return std_map_get(es->rootObjects, &name);
}

void Esther_setRootObject(Esther *es, const struct string name, Object *value) {
    // @THIS
    struct string *str = malloc(sizeof(struct string));
    *str = string_copy(name);
    std_map_set(es->rootObjects, str, value);
}

static void error_invalidAST(Esther *es) {
    Exception_throw_new(es, "invalid AST");
}

Object *Esther_eval(Esther *es, Object *ast, Context *context) {
    if (Object_getType(ast) == TString) {
        Object *tokens = Lexer_lex(es, es->lexer, ast);
        ast = Parser_parse(es, es->parser, tokens);
    }

    if (Object_getType(ast) != TTuple)
        error_invalidAST(es);

    if (Tuple_size(ast) == 0)
        return es->nullObject;

    Id id = Symbol_getId(Tuple_get(ast, 0));

    Object *value = es->nullObject;

    TRY {
        if (id == id_braces) {
            Object *nodes = Tuple_get(ast, 2);

            for (size_t i = 0; i < Array_size(nodes); i++)
                value = Esther_eval(es, Array_get(nodes, i), context);
        }

        else if (id == id_class) {
            struct string name = String_value(Tuple_get(ast, 2));

            Object *superclass = Tuple_size(ast) == 5 ? Esther_eval(es, Tuple_get(ast, 3), context) : NULL;

            Object *_class = Class_new_init(es, name, superclass);

            if (name.size > 0)
                Context_setLocal(context, name, _class);

            Esther_eval(es, Tuple_get(ast, superclass ? 4 : 3), Context_childContext(context, _class, Object_new(es)));

            value = _class;
        }

        else if (id == id_assign) {
            Object *child = Tuple_get(ast, 2);
            Id childId = Symbol_getId(Tuple_get(child, 0));

            value = Esther_eval(es, Tuple_get(ast, 3), context);

            if (childId == id_attr)
                Object_setAttribute(Esther_eval(es, Tuple_get(child, 2), context), String_value(Tuple_get(child, 3)), value);
            else if (childId == id_id) {
                struct string name = String_value(Tuple_get(child, 2));

                if (!Context_assign(context, name, value))
                    Context_setLocal(context, name, value);
            }
        }

        else if (id == id_plus) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("+"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_plusAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("+="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_minus) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("-"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_minusAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("-="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_multiply) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("*"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_multiplyAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("*="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_divide) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("/"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_divideAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("/="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_mod) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("%"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_modAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("%="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_power) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("**"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_powerAssign) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("**="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        }

        else if (id == id_lt) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("<"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_gt) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const(">"), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_le) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("<="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_ge) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const(">="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_eq) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("=="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_ne) {
            Object *left = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Object_call(es, left, string_const("!="), Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 3), context)));
        }

        else if (id == id_or) {
            value = Esther_toBoolean(es, Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)) || Object_isTrue(Esther_eval(es, Tuple_get(ast, 3), context)));
        } else if (id == id_and) {
            value = Esther_toBoolean(es, Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)) && Object_isTrue(Esther_eval(es, Tuple_get(ast, 3), context)));
        }

        else if (id == id_if) {
            if (Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)))
                value = Esther_eval(es, Tuple_get(ast, 3), context);
            else if (Tuple_size(ast) == 5)
                value = Esther_eval(es, Tuple_get(ast, 4), context);
            else
                value = es->nullObject;
        }

        else if (id == id_while) {
            Object *condition = Tuple_get(ast, 2);
            Object *body = Tuple_get(ast, 3);

            while (Object_isTrue(Esther_eval(es, condition, context)))
                value = Esther_eval(es, body, context);
        }

        else if (id == id_true) {
            value = es->trueObject;
        } else if (id == id_false) {
            value = es->falseObject;
        } else if (id == id_null) {
            value = es->nullObject;
        }

        else if (id == id_self) {
            value = Context_getSelf(context);
        } else if (id == id_here) {
            value = Context_getHere(context);
        }

        else if (id == id_pars) {
            Object *nodes = Tuple_get(ast, 2);
            Object *tuple = Tuple_new_init_null(es, Array_size(nodes));

            for (size_t i = 0; i < Array_size(nodes); i++)
                Tuple_set(tuple, i, Esther_eval(es, Array_get(nodes, i), context));

            value = tuple;
        }

        else if (id == id_brackets) {
            Object *nodes = Tuple_get(ast, 2);
            Object *array = Array_new(es, 0);

            for (size_t i = 0; i < Array_size(nodes); i++)
                Array_push(array, Esther_eval(es, Array_get(nodes, i), context));

            value = array;
        }

        else if (id == id_attr) {
            Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 2), context);
            struct string name = String_value(Tuple_get(ast, 3));
            value = Object_resolve(evaledSelf, name);

            if (!value)
                // @Temp: C-string
                Exception_throw_new(es, "undefined attribute '%s'", name.data);
        }

        else if (id == id_new) {
            if (Tuple_size(ast) == 3) {
                Object *newObject = Object_new(es);
                Esther_eval(es, Tuple_get(ast, 2), Context_childContext(context, newObject, Object_new(es)));
                value = newObject;
            } else if (Tuple_size(ast) == 5) {
                Object *evaledSelf = Context_resolve(es, context, String_value(Tuple_get(ast, 2)));

                Object *args = Tuple_get(ast, 3);
                Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

                for (size_t i = 0; i < Array_size(args); i++)
                    Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

                Object *instance = Object_call(es, evaledSelf, string_const("new"), evaledArgs);

                Esther_eval(es, Tuple_get(ast, 4), Context_childContext(context, instance, Object_new(es)));

                value = instance;
            } else
                value = NULL;
        }

        else if (id == id_function) {
            struct string name = String_value(Tuple_get(ast, 2));
            Object *f = InterpretedFunction_new(es, name, Tuple_get(ast, 3), context, Tuple_get(ast, 4));

            if (name.size > 0) {
                Context_setLocal(context, name, f);

                Object *self = Context_getSelf(context);

                if (Object_getType(self) == TClass)
                    Class_setMethod(self, name, f);
            }

            value = f;
        }

        else if (id == id_call) {
            Object *evaledSelf;
            Object *evaledF;

            Object *child = Tuple_get(ast, 2);
            Id childId = Symbol_getId(Tuple_get(child, 0));

            if (childId == id_attr) {
                struct string name = String_value(Tuple_get(child, 3));

                evaledSelf = Esther_eval(es, Tuple_get(child, 2), context);
                evaledF = Object_resolve(evaledSelf, name);

                if (!evaledF)
                    // @Temp: C-string
                    Exception_throw_new(es, "undefined attribute '%s'", name.data);
            } else if (childId == id_dot) {
                evaledSelf = Esther_eval(es, Tuple_get(child, 2), context);
                evaledF = Esther_eval(es, Tuple_get(child, 3), Context_childContext(context, evaledSelf, Object_new(es)));
            } else {
                evaledSelf = Context_getSelf(context);
                evaledF = Esther_eval(es, child, context);
            }

            Object *args = Tuple_get(ast, 3);

            Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

            for (size_t i = 0; i < Array_size(args); i++)
                Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

            value = Object_call_function(es, evaledSelf, evaledF, evaledArgs);
        }

        else if (id == id_id) {
            struct string name = String_value(Tuple_get(ast, 2));
            value = Context_resolve(es, context, name);

            if (!value)
                // @Temp: C-string
                Exception_throw_new(es, "undefined variable '%s'", name.data);
        }

        else if (id == id_var) {
            struct string name = String_value(Tuple_get(ast, 2));
            value = Tuple_size(ast) == 4 ? Tuple_get(ast, 3) : es->nullObject;

            Context_setLocal(context, name, value);
        }

        else if (id == id_dot) {
            Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 2), context);
            value = Esther_eval(es, Tuple_get(ast, 3), Context_childContext(context, evaledSelf, Object_new(es)));
        }

        else if (id == id_sharp) {
            value = Tuple_get(ast, 2);

            if (Object_getType(value) == TValueObject)
                value = ValueObject_new_var(es, ValueObject_getValue(value));
            else if (Object_getType(value) == TString)
                value = String_new(es, String_value(value));
        }

        else if (id == id_colon) {
            value = Symbol_new(es, String_value(Tuple_get(ast, 2)));
        }

        else if (id == id_not) {
            value = Esther_toBoolean(es, !Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)));
        }
    }
    CATCH(e) {
        if (Tuple_size(ast) > 0) {
            Object *pos = Tuple_get(Tuple_get(ast, 1), 0);

            if (Exception_getPos(e) == NULL && Tuple_size(pos) > 0)
                Exception_setPos(e, pos);
        }

        Exception_throw(e);
    }
    ENDTRY;

    return value;
}

void Esther_runFile(Esther *es, const char *fileName) {
    struct FileRecord rec;

    rec.fileName = full_path(fileName);
    rec.source = NULL;
    rec.next = es->file;

    es->file = &rec;

    TRY {
        struct string rawCode = read_file(fileName);

        if (!rawCode.data) {
            printf("error: unable to read file\n");
            pop_jump_buffer();
            break;
        }

        Object *code = String_new_move(es, string_expand_tabs(rawCode));
        Object_setAttribute(es->esther, string_const("code"), code);

        es->file->source = code;

        string_free(rawCode);

        Object *tokens = Lexer_lex(es, es->lexer, code);
        Object_setAttribute(es->esther, string_const("tokens"), tokens);

        // IO_writeLine(es, tokens, Tuple_new(es, 0));

        Object *ast = Parser_parse(es, es->parser, tokens);
        Object_setAttribute(es->esther, string_const("ast"), ast);

        // IO_writeLine(es, ast, Tuple_new(es, 0));

        Object *value = Esther_eval(es, ast, es->root);

        printf("=> %s\n", String_c_str(Object_inspect(es, value)));
    }
    CATCH(e) {
        Object *pos = Exception_getPos(e);

        if (pos != NULL && es->file && es->file->source) {
            int offset = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 0)));
            int line = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 1)));
            int column = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 2)));

            // @Temp: C-string
            struct string q = string_quote(String_value(es->file->source), offset, column);
            printf("%s:%i:%i: error: %s\n%s\n", es->file->fileName, line, column, Exception_getMessage(e).data, q.data);
            string_free(q);
        } else
            // @Temp: C-string
            printf("error: %s\n", Exception_getMessage(e).data);
    }
    ENDTRY;

    free((void *) es->file->fileName);

    es->file = es->file->next;
}
