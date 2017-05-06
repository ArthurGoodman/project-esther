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
    return String_new(es, "");
}

static Object *SymbolClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Symbol_new(es, "");
}

static Object *FunctionClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw(es, "cannot create an instance of Function class yet...");
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Tuple_new(es, 0);
}

static Object *ArrayClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Array_new(es, 0);
}

static Object *BooleanClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw(es, "cannot create an instance of Boolean class");
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw(es, "cannot create an instance of Null class");
    return NULL;
}

static Object *NumericClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    Exception_throw(es, "cannot create an instance of Numeric class");
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
            Exception_throw(es, "invalid argument");
            return NULL;
        }
    }

    Exception_throw(es, "invalid number of arguments");
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
            Exception_throw(es, "invalid argument");
            return NULL;
        }
    }

    Exception_throw(es, "invalid number of arguments");
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
            Exception_throw(es, "invalid argument");
            return NULL;
        }
    }

    Exception_throw(es, "invalid number of arguments");
    return NULL;
}

static Object *ExceptionClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Exception_new(es, "");
}

static Object *True_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new(es, "true");
}

static Object *False_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new(es, "false");
}

static bool False_virtual_isTrue() {
    return false;
}

static Object *Null_virtual_toString(Esther *es, Object *UNUSED(self)) {
    return String_new(es, "null");
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
        Exception_throw(es, "invalid arguments");

    if (Object_getType(Tuple_get(args, 1)) != TTuple)
        Exception_throw(es, "invalid arguments");

    return Class_newInstance(es, self, Tuple_get(args, 1));
}

static Object *ClassClass_hasMethod(Esther *es, Object *self, Object *name) {
    return Esther_toBoolean(es, Class_hasMethod(self, String_c_str(name)));
}

static Object *ClassClass_getMethod(Esther *UNUSED(es), Object *self, Object *name) {
    return Class_getMethod(self, String_c_str(name));
}

static Object *ClassClass_setMethod(Esther *UNUSED(es), Object *self, Object *name, Object *method) {
    Class_setMethod(self, String_c_str(name), method);
    return method;
}

static Object *StringClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, String_size(self));
}

static Object *StringClass_at(Esther *es, Object *self, Object *pos) {
    return ValueObject_new_char(es, String_c_str(self)[Variant_toInt(ValueObject_getValue(pos))]);
}

static Object *StringClass_plus(Esther *es, Object *self, Object *str) {
    return String_append(String_new(es, String_c_str(self)), Object_toString(es, str));
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

static Object *TupleClass_at(Esther *es, Object *self, Object *index) {
    return Tuple_get(self, Variant_toInt(ValueObject_getValue(index)));
}

static Object *TupleClass_set(Esther *es, Object *self, Object *index, Object *value) {
    Tuple_set(self, Variant_toInt(ValueObject_getValue(index)), value);
    return value;
}

static Object *ArrayClass_size(Esther *es, Object *self) {
    return ValueObject_new_int(es, Array_size(self));
}

static Object *ArrayClass_at(Esther *es, Object *self, Object *index) {
    return Array_get(self, Variant_toInt(ValueObject_getValue(index)));
}

static Object *ArrayClass_set(Esther *es, Object *self, Object *index, Object *value) {
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

static void GlobalMapper_mapOnReferences(GlobalMapper *self, MapFunction f) {
    f((void **)&self->es->objectClass);
    f((void **)&self->es->classClass);
    f((void **)&self->es->stringClass);
    f((void **)&self->es->symbolClass);
    f((void **)&self->es->functionClass);
    f((void **)&self->es->tupleClass);
    f((void **)&self->es->arrayClass);
    f((void **)&self->es->booleanClass);
    f((void **)&self->es->nullClass);
    f((void **)&self->es->numericClass);
    f((void **)&self->es->charClass);
    f((void **)&self->es->intClass);
    f((void **)&self->es->floatClass);
    f((void **)&self->es->exceptionClass);

    f((void **)&self->es->trueObject);
    f((void **)&self->es->falseObject);
    f((void **)&self->es->nullObject);

    f((void **)&self->es->lexer);
    f((void **)&self->es->parser);

    f((void **)&self->es->mainObject);
    f((void **)&self->es->esther);
    f((void **)&self->es->io);

    f((void **)&self->es->root);

#define X(a, b) f((void **)&sym_##a);
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X
}

static Mapper *GlobalMapper_new(Esther *es) {
    GlobalMapper *self = malloc(sizeof(GlobalMapper));
    self->base.mapOnReferences = (void (*)(Mapper *, MapFunction))GlobalMapper_mapOnReferences;
    self->es = es;
    return (Mapper *)self;
}

void Esther_init(Esther *es) {
    uint8_t local;
    gc_initialize((ptr_ptr_t)&local);

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

    es->classClass = Class_new_init(es, "Class", NULL);
    as_Class(es->classClass)->base.objectClass = es->classClass;
    as_Class(es->classClass)->newInstance = ClassClass_virtual_newInstance;

    es->objectClass = NULL;
    es->objectClass = Class_new_init(es, "Object", NULL);
    as_Class(es->classClass)->superclass = es->objectClass;
    as_Class(es->objectClass)->newInstance = ObjectClass_virtual_newInstance;

    es->stringClass = Class_new_init(es, "String", NULL);
    as_Class(es->stringClass)->newInstance = StringClass_virtual_newInstance;

    es->symbolClass = Class_new_init(es, "Symbol", NULL);
    as_Class(es->symbolClass)->newInstance = SymbolClass_virtual_newInstance;

    es->functionClass = Class_new_init(es, "Function", NULL);
    as_Class(es->functionClass)->newInstance = FunctionClass_virtual_newInstance;

    es->tupleClass = Class_new_init(es, "Tuple", NULL);
    as_Class(es->tupleClass)->newInstance = TupleClass_virtual_newInstance;

    es->arrayClass = Class_new_init(es, "Array", NULL);
    as_Class(es->arrayClass)->newInstance = ArrayClass_virtual_newInstance;

    es->booleanClass = Class_new_init(es, "Boolean", NULL);
    as_Class(es->booleanClass)->newInstance = BooleanClass_virtual_newInstance;

    es->nullClass = Class_new_init(es, "Null", NULL);
    as_Class(es->nullClass)->newInstance = NullClass_virtual_newInstance;

    es->numericClass = Class_new_init(es, "Numeric", NULL);
    as_Class(es->numericClass)->newInstance = NumericClass_virtual_newInstance;

    es->charClass = Class_new_init(es, "Char", es->numericClass);
    as_Class(es->charClass)->newInstance = CharClass_virtual_newInstance;

    es->intClass = Class_new_init(es, "Int", es->numericClass);
    as_Class(es->intClass)->newInstance = IntClass_virtual_newInstance;

    es->floatClass = Class_new_init(es, "Float", es->numericClass);
    as_Class(es->floatClass)->newInstance = FloatClass_virtual_newInstance;

    es->exceptionClass = Class_new_init(es, "Exception", NULL);
    as_Class(es->exceptionClass)->newInstance = ExceptionClass_virtual_newInstance;

    es->trueObject = Object_new(es);
    es->trueObject->objectClass = es->booleanClass;
    es->trueObject->toString = es->trueObject->inspect = True_virtual_toString;

    es->falseObject = Object_new(es);
    es->falseObject->objectClass = es->booleanClass;
    es->falseObject->toString = es->falseObject->inspect = False_virtual_toString;
    es->falseObject->isTrue = False_virtual_isTrue;

    es->nullObject = Object_new(es);
    es->nullObject->objectClass = es->nullClass;
    es->nullObject->toString = es->nullObject->inspect = Null_virtual_toString;
    es->nullObject->isTrue = False_virtual_isTrue;

    Class_setMethod_func(es->objectClass, Function_new(es, "class", (Object * (*)()) ObjectClass_class, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "toString", (Object * (*)()) Object_toString, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "inspect", (Object * (*)()) Object_inspect, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "equals", (Object * (*)()) ObjectClass_equals, 1));
    Class_setMethod(es->objectClass, "==", Class_getMethod(es->objectClass, "equals"));

    Class_setMethod_func(es->classClass, Function_new(es, "superclass", (Object * (*)()) ClassClass_superclass, 0));
    Class_setMethod_func(es->classClass, Function_new(es, "new", (Object * (*)()) Class_newInstance, -1));
    Class_setMethod_func(es->classClass, Function_new(es, "()", (Object * (*)()) ClassClass_pars, -1));
    Class_setMethod_func(es->classClass, Function_new(es, "hasMethod", (Object * (*)()) ClassClass_hasMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, "getMethod", (Object * (*)()) ClassClass_getMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, "setMethod", (Object * (*)()) ClassClass_setMethod, 2));

    Class_setMethod_func(es->stringClass, Function_new(es, "size", (Object * (*)()) StringClass_size, 0));
    Class_setMethod_func(es->stringClass, Function_new(es, "at", (Object * (*)()) StringClass_at, 1));
    Class_setMethod(es->stringClass, "[]", Class_getMethod(es->stringClass, "at"));
    Class_setMethod_func(es->stringClass, Function_new(es, "+", (Object * (*)()) StringClass_plus, 1));
    Class_setMethod_func(es->stringClass, Function_new(es, "append", (Object * (*)()) StringClass_append, 1));
    Class_setMethod(es->stringClass, "+=", Class_getMethod(es->stringClass, "append"));
    Class_setMethod_func(es->stringClass, Function_new(es, "contains", (Object * (*)()) StringClass_contains, 1));

    Class_setMethod_func(es->functionClass, Function_new(es, "call", (Object * (*)()) Function_invoke, 2));
    Class_setMethod(es->functionClass, "()", Class_getMethod(es->functionClass, "call"));

    Class_setMethod_func(es->tupleClass, Function_new(es, "size", (Object * (*)()) TupleClass_size, 0));
    Class_setMethod_func(es->tupleClass, Function_new(es, "at", (Object * (*)()) TupleClass_at, 1));
    Class_setMethod(es->tupleClass, "[]", Class_getMethod(es->tupleClass, "at"));
    Class_setMethod_func(es->tupleClass, Function_new(es, "set", (Object * (*)()) TupleClass_set, 2));

    Class_setMethod_func(es->arrayClass, Function_new(es, "size", (Object * (*)()) ArrayClass_size, 0));
    Class_setMethod_func(es->arrayClass, Function_new(es, "at", (Object * (*)()) ArrayClass_at, 1));
    Class_setMethod(es->arrayClass, "[]", Class_getMethod(es->arrayClass, "at"));
    Class_setMethod_func(es->arrayClass, Function_new(es, "set", (Object * (*)()) ArrayClass_set, 2));

    Class_setMethod_func(es->numericClass, Function_new(es, "+", (Object * (*)()) NumericClass_add, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "+=", (Object * (*)()) NumericClass_addAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "-", (Object * (*)()) NumericClass_sub, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "-=", (Object * (*)()) NumericClass_subAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "*", (Object * (*)()) NumericClass_mul, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "*=", (Object * (*)()) NumericClass_mulAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "/", (Object * (*)()) NumericClass_div, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "/=", (Object * (*)()) NumericClass_divAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "%", (Object * (*)()) NumericClass_mod, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "%=", (Object * (*)()) NumericClass_modAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "**", (Object * (*)()) NumericClass_pow, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "**=", (Object * (*)()) NumericClass_powAssign, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "<", (Object * (*)()) NumericClass_lt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, ">", (Object * (*)()) NumericClass_gt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "<=", (Object * (*)()) NumericClass_lte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, ">=", (Object * (*)()) NumericClass_gte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "==", (Object * (*)()) NumericClass_eq, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "!=", (Object * (*)()) NumericClass_ne, 1));

    Class_setMethod_func(es->charClass, Function_new(es, "isSpace", (Object * (*)()) CharClass_isSpace, 0));
    Class_setMethod_func(es->charClass, Function_new(es, "isDigit", (Object * (*)()) CharClass_isDigit, 0));
    Class_setMethod_func(es->charClass, Function_new(es, "isLetter", (Object * (*)()) CharClass_isLetter, 0));
    Class_setMethod_func(es->charClass, Function_new(es, "isLetterOrDigit", (Object * (*)()) CharClass_isLetterOrDigit, 0));

    es->lexer = Lexer_new(es);

    Object_setAttribute(es->lexer, "lex", Function_new(es, "lex", (Object * (*)()) Lexer_lex, 1));

    es->parser = Parser_new(es);

    Object_setAttribute(es->parser, "parse", Function_new(es, "parse", (Object * (*)()) Parser_parse, 1));

    es->mainObject = Object_new(es);

    es->esther = Object_new(es);

    Object_setAttribute(es->esther, "lexer", es->lexer);
    Object_setAttribute(es->esther, "parser", es->parser);
    Object_setAttribute(es->esther, "eval", Function_new(es, "eval", (Object * (*)()) Esther_evalFunction, 1));

    es->io = Object_new(es);

    Object_setAttribute(es->io, "write", Function_new(es, "write", (Object * (*)()) IO_write, -1));
    Object_setAttribute(es->io, "writeLine", Function_new(es, "writeLine", (Object * (*)()) IO_writeLine, -1));

    es->root = Context_new(es);

    es->rootObjects = std_map_new(string_compare);

    Esther_setRootObject(es, "Object", es->objectClass);
    Esther_setRootObject(es, "Class", es->classClass);
    Esther_setRootObject(es, "String", es->stringClass);
    Esther_setRootObject(es, "Symbol", es->symbolClass);
    Esther_setRootObject(es, "Function", es->functionClass);
    Esther_setRootObject(es, "Tuple", es->tupleClass);
    Esther_setRootObject(es, "Array", es->arrayClass);
    Esther_setRootObject(es, "Boolean", es->booleanClass);
    Esther_setRootObject(es, "Null", es->nullClass);
    Esther_setRootObject(es, "Numeric", es->numericClass);
    Esther_setRootObject(es, "Char", es->charClass);
    Esther_setRootObject(es, "Int", es->intClass);
    Esther_setRootObject(es, "Float", es->floatClass);

    Esther_setRootObject(es, "IO", es->io);
    Esther_setRootObject(es, "esther", es->esther);

    init_identifiers(es);
}

Object *Esther_toBoolean(Esther *es, bool value) {
    return value ? es->trueObject : es->falseObject;
}

bool Esther_hasRootObject(Esther *es, const char *name) {
    return std_map_contains(es->rootObjects, name);
}

Object *Esther_getRootObject(Esther *es, const char *name) {
    return std_map_get(es->rootObjects, name);
}

void Esther_setRootObject(Esther *es, const char *name, Object *value) {
    std_map_set(es->rootObjects, name, value);
}

static void error_invalidAST(Esther *es) {
    Exception_throw(es, "invalid AST");
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

    if (id == id_braces) {
        Object *nodes = Tuple_get(ast, 1);

        Object *value = es->nullObject;

        for (size_t i = 0; i < Array_size(nodes); i++)
            value = Esther_eval(es, Array_get(nodes, i), context);

        return value;
    }

    else if (id == id_class) {
        const char *name = String_c_str(Tuple_get(ast, 1));

        Object *superclass = Tuple_size(ast) == 4 ? Esther_eval(es, Tuple_get(ast, 2), context) : NULL;

        Object *_class = Class_new_init(es, name, superclass);

        if (strlen(name) > 0)
            Context_setLocal(context, name, _class);

        Esther_eval(es, Tuple_get(ast, superclass ? 3 : 2), Context_childContext(context, _class, Object_new(es)));

        return _class;
    }

    else if (id == id_assign) {
        Object *child = Tuple_get(ast, 1);
        Id childId = Symbol_getId(Tuple_get(child, 0));

        Object *value = Esther_eval(es, Tuple_get(ast, 2), context);

        if (childId == id_attr)
            Object_setAttribute(Esther_eval(es, Tuple_get(child, 1), context), String_c_str(Tuple_get(child, 2)), value);
        else if (childId == id_id) {
            const char *name = String_c_str(Tuple_get(child, 1));

            if (!Context_assign(context, name, value))
                Context_setLocal(context, name, value);
        }

        return value;
    }

    else if (id == id_plus) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "+", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_plusAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "+=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_minus) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "-", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_minusAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "-=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_multiply) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "*", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_multiplyAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "*=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_divide) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "/", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_divideAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "/=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_mod) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "%", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_modAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "%=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_power) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "**", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_powerAssign) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "**=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    }

    else if (id == id_lt) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "<", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_gt) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, ">", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_le) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "<=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_ge) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, ">=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_eq) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "==", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_ne) {
        Object *left = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_call(es, left, "!=", Tuple_new(es, 1, Esther_eval(es, Tuple_get(ast, 2), context)));
    }

    else if (id == id_or) {
        return Esther_toBoolean(es, Object_isTrue(Esther_eval(es, Tuple_get(ast, 1), context)) || Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)));
    } else if (id == id_and) {
        return Esther_toBoolean(es, Object_isTrue(Esther_eval(es, Tuple_get(ast, 1), context)) && Object_isTrue(Esther_eval(es, Tuple_get(ast, 2), context)));
    }

    else if (id == id_if) {
        if (Object_isTrue(Esther_eval(es, Tuple_get(ast, 1), context)))
            return Esther_eval(es, Tuple_get(ast, 2), context);
        else if (Tuple_size(ast) == 4)
            return Esther_eval(es, Tuple_get(ast, 3), context);
        else
            return es->nullObject;
    }

    else if (id == id_while) {
        Object *value = es->nullObject;

        Object *condition = Tuple_get(ast, 1);
        Object *body = Tuple_get(ast, 2);

        while (Object_isTrue(Esther_eval(es, condition, context)))
            value = Esther_eval(es, body, context);

        return value;
    }

    else if (id == id_true) {
        return es->trueObject;
    } else if (id == id_false) {
        return es->falseObject;
    } else if (id == id_null) {
        return es->nullObject;
    }

    else if (id == id_self) {
        return Context_getSelf(context);
    } else if (id == id_here) {
        return Context_getHere(context);
    }

    else if (id == id_pars) {
        Object *nodes = Tuple_get(ast, 1);
        Object *tuple = Tuple_new_init_null(es, Array_size(nodes));

        for (size_t i = 0; i < Array_size(nodes); i++)
            Tuple_set(tuple, i, Esther_eval(es, Array_get(nodes, i), context));

        return tuple;
    }

    else if (id == id_brackets) {
        Object *nodes = Tuple_get(ast, 1);
        Object *array = Array_new(es, 0);

        for (size_t i = 0; i < Array_size(nodes); i++)
            Array_push(array, Esther_eval(es, Array_get(nodes, i), context));

        return array;
    }

    else if (id == id_attr) {
        Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 1), context);
        const char *name = String_c_str(Tuple_get(ast, 2));
        Object *value = Object_resolve(evaledSelf, name);

        if (!value)
            Exception_throw(es, "undefined attribute '%s'", name);

        return value;
    }

    else if (id == id_new) {
        if (Tuple_size(ast) == 2) {
            Object *newObject = Object_new(es);
            Esther_eval(es, Tuple_get(ast, 1), Context_childContext(context, newObject, Object_new(es)));
            return newObject;
        } else if (Tuple_size(ast) == 4) {
            Object *evaledSelf = Context_resolve(es, context, String_c_str(Tuple_get(ast, 1)));

            Object *args = Tuple_get(ast, 2);
            Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

            for (size_t i = 0; i < Array_size(args); i++)
                Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

            Object *instance = Object_call(es, evaledSelf, "new", evaledArgs);

            Esther_eval(es, Tuple_get(ast, 3), Context_childContext(context, instance, Object_new(es)));

            return instance;
        } else
            return NULL;
    }

    else if (id == id_function) {
        const char *name = String_c_str(Tuple_get(ast, 1));
        Object *f = InterpretedFunction_new(es, name, Tuple_get(ast, 2), context, Tuple_get(ast, 3));

        if (strlen(name) > 0) {
            Context_setLocal(context, name, f);

            Object *self = Context_getSelf(context);

            if (Object_getType(self) == TClass)
                Class_setMethod(self, name, f);
        }

        return f;
    }

    else if (id == id_call) {
        Object *evaledSelf;
        Object *evaledF;

        Object *child = Tuple_get(ast, 1);
        Id childId = Symbol_getId(Tuple_get(child, 0));

        if (childId == id_attr) {
            const char *name = String_c_str(Tuple_get(child, 2));

            evaledSelf = Esther_eval(es, Tuple_get(child, 1), context);
            evaledF = Object_resolve(evaledSelf, name);

            if (!evaledF)
                Exception_throw(es, "undefined attribute '%s'", name);
        } else if (childId == id_dot) {
            evaledSelf = Esther_eval(es, Tuple_get(child, 1), context);
            evaledF = Esther_eval(es, Tuple_get(child, 2), Context_childContext(context, evaledSelf, Object_new(es)));
        } else {
            evaledSelf = Context_getSelf(context);
            evaledF = Esther_eval(es, child, context);
        }

        Object *args = Tuple_get(ast, 2);

        Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

        for (size_t i = 0; i < Array_size(args); i++)
            Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

        return Object_call_function(es, evaledSelf, evaledF, evaledArgs);
    }

    else if (id == id_id) {
        const char *name = String_c_str(Tuple_get(ast, 1));
        Object *value = Context_resolve(es, context, name);

        if (!value)
            Exception_throw(es, "undefined variable '%s'", name);

        return value;
    }

    else if (id == id_var) {
        const char *name = String_c_str(Tuple_get(ast, 1));
        Object *value = Tuple_size(ast) == 3 ? Tuple_get(ast, 2) : es->nullObject;

        Context_setLocal(context, name, value);

        return value;
    }

    else if (id == id_dot) {
        Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 1), context);
        return Esther_eval(es, Tuple_get(ast, 2), Context_childContext(context, evaledSelf, Object_new(es)));
    }

    else if (id == id_sharp) {
        Object *value = Tuple_get(ast, 1);

        if (Object_getType(value) == TValueObject)
            return ValueObject_new_var(es, ValueObject_getValue(value));
        else if (Object_getType(value) == TString)
            return String_new(es, String_c_str(value));
    }

    else if (id == id_colon) {
        return Symbol_new(es, String_c_str(Tuple_get(ast, 1)));
    }

    else if (id == id_not) {
        return Esther_toBoolean(es, !Object_isTrue(Esther_eval(es, Tuple_get(ast, 1), context)));
    }

    return NULL;
}

void Esther_runFile(Esther *es, const char *fileName) {
    TRY {
        Object *code = String_new_std(es, read_file(fileName));
        Object_setAttribute(es->esther, "code", code);

        Object *tokens = Lexer_lex(es, es->lexer, code);
        Object_setAttribute(es->esther, "tokens", tokens);

        IO_writeLine(es, tokens, Tuple_new(es, 0));

        Object *ast = Parser_parse(es, es->parser, tokens);
        Object_setAttribute(es->esther, "ast", ast);

        IO_writeLine(es, ast, Tuple_new(es, 0));

        Object *value = Esther_eval(es, ast, es->root);
        printf("=> %s\n", String_c_str(Object_inspect(es, value)));
    }
    CATCH(e) {
        printf("error: %s\n", Exception_getMessage(e));
    }
    ENDTRY;
}
