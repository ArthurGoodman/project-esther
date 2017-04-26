#include "esther/esther.h"

#include "esther/array.h"
#include "esther/class.h"
#include "esther/context.h"
#include "esther/function.h"
#include "esther/object.h"
#include "esther/std_map.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/valueobject.h"

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

static Object *FunctionClass_virtual_newInstance(Esther *UNUSED(esther), Object *UNUSED(self), Object *UNUSED(args)) {
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Tuple_new(es, 0);
}

static Object *ArrayClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    return Array_new(es, 0);
}

static Object *BooleanClass_virtual_newInstance(Esther *UNUSED(esther), Object *UNUSED(self), Object *UNUSED(args)) {
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *UNUSED(esther), Object *UNUSED(self), Object *UNUSED(args)) {
    return NULL;
}

static Object *NumericClass_virtual_newInstance(Esther *UNUSED(esther), Object *UNUSED(self), Object *UNUSED(args)) {
    return NULL;
}

static Object *CharClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *args) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_char(es, '\0');

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), es->numericClass))
            return NULL;

        return ValueObject_new_char(es, Variant_toChar(as_ValueObject(Tuple_get(args, 0))->value));
    }

    return NULL;
}

static Object *IntClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_int(es, 0);

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), es->numericClass))
            return NULL;

        return ValueObject_new_int(es, Variant_toInt(as_ValueObject(Tuple_get(args, 0))->value));
    }

    return NULL;
}

static Object *FloatClass_virtual_newInstance(Esther *es, Object *UNUSED(self), Object *UNUSED(args)) {
    if (Tuple_size(args) == 0)
        return ValueObject_new_real(es, 0.0);

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), es->numericClass))
            return NULL;

        return ValueObject_new_real(es, Variant_toReal(as_ValueObject(Tuple_get(args, 0))->value));
    }

    return NULL;
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

static Object *ObjectClass_class(Esther *UNUSED(esther), Object *self) {
    return Object_getClass(self);
}

static Object *ObjectClass_equals(Esther *es, Object *self, Object *obj) {
    return Esther_toBoolean(es, Object_equals(es, self, obj));
}

static Object *ClassClass_superclass(Esther *UNUSED(esther), Object *self) {
    return Class_getSuperclass(self);
}

static Object *ClassClass_hasMethod(Esther *es, Object *self, Object *name) {
    return Esther_toBoolean(es, Class_hasMethod(self, String_c_str(name)));
}

static Object *ClassClass_getMethod(Esther *UNUSED(esther), Object *self, Object *name) {
    return Class_getMethod(self, String_c_str(name));
}

static Object *ClassClass_setMethod(Esther *UNUSED(esther), Object *self, Object *name, Object *method) {
    Class_setMethod(self, String_c_str(name), method);
    return method;
}

static Object *NumericClass_add(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_add(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_sub(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_sub(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_mul(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_mul(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_div(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_div(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_mod(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_mod(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_pow(Esther *es, Object *a, Object *b) {
    return ValueObject_new_var(es, Variant_pow(ValueObject_getValue(a), ValueObject_getValue(b)));
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

void Esther_init(Esther *es) {
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

    Class_setMethod_func(es->objectClass, Function_new(es, "class", (Object * (*)())ObjectClass_class, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "toString", (Object * (*)())Object_toString, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "inspect", (Object * (*)())Object_inspect, 0));
    Class_setMethod_func(es->objectClass, Function_new(es, "equals", (Object * (*)())ObjectClass_equals, 1));
    Class_setMethod(es->objectClass, "==", Class_getMethod(es->objectClass, "equals"));

    Class_setMethod_func(es->classClass, Function_new(es, "superclass", (Object * (*)())ClassClass_superclass, 0));
    Class_setMethod_func(es->classClass, Function_new(es, "new", (Object * (*)())Class_newInstance, -1));
    Class_setMethod(es->classClass, "()", Class_getMethod(es->classClass, "new"));
    Class_setMethod_func(es->classClass, Function_new(es, "hasMethod", (Object * (*)())ClassClass_hasMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, "getMethod", (Object * (*)())ClassClass_getMethod, 1));
    Class_setMethod_func(es->classClass, Function_new(es, "setMethod", (Object * (*)())ClassClass_setMethod, 2));

    Class_setMethod_func(es->numericClass, Function_new(es, "+", (Object * (*)())NumericClass_add, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "-", (Object * (*)())NumericClass_sub, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "*", (Object * (*)())NumericClass_mul, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "/", (Object * (*)())NumericClass_div, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "%", (Object * (*)())NumericClass_mod, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "^", (Object * (*)())NumericClass_pow, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "<", (Object * (*)())NumericClass_lt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, ">", (Object * (*)())NumericClass_gt, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "<=", (Object * (*)())NumericClass_lte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, ">=", (Object * (*)())NumericClass_gte, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "==", (Object * (*)())NumericClass_eq, 1));
    Class_setMethod_func(es->numericClass, Function_new(es, "!=", (Object * (*)())NumericClass_ne, 1));

    es->mainObject = Object_new(es);

    es->io = Object_new(es);

    Object_setAttribute(es->io, "write", Function_new(es, "write", (Object * (*)())IO_write, -1));
    Object_setAttribute(es->io, "writeLine", Function_new(es, "writeLine", (Object * (*)())IO_writeLine, -1));

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

Object *Esther_eval(Esther *es, Object *ast, Context *context) {
    Id id_brace = stringToId("{}");
    Id id_class = stringToId("class");
    Id id_eq = stringToId("=");
    Id id_self = stringToId("self");
    Id id_attr = stringToId("attr");
    Id id_new = stringToId("new");
    Id id_function = stringToId("function");
    Id id_call = stringToId("call");
    Id id_id = stringToId("id");
    Id id_sharp = stringToId("#");
    Id id_dot = stringToId(".");

    if (Tuple_size(ast) == 0)
        return es->nullObject;

    Id id = Symbol_getId(Tuple_get(ast, 0));

    if (id == id_brace) {
        Object *nodes = Tuple_get(ast, 1);

        Object *value = es->nullObject;

        for (size_t i = 0; i < Array_size(nodes); i++)
            value = Esther_eval(es, Array_get(nodes, i), context);

        return value;
    } else if (id == id_class) {
        const char *name = String_c_str(Tuple_get(ast, 1));
        Object *_class = Class_new_init(es, name, NULL);

        Context *child = Context_childContext(context, _class, Object_new(es));
        Esther_eval(es, Tuple_get(ast, 2), child);

        if (strlen(name) > 0)
            Context_setLocal(context, name, _class);

        return _class;
    } else if (id == id_eq) {
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
    } else if (id == id_self) {
        return Context_getSelf(context);
    } else if (id == id_attr) {
        Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 1), context);
        return Object_getAttribute(evaledSelf, String_c_str(Tuple_get(ast, 2)));
    } else if (id == id_new) {
        if (Tuple_size(ast) == 3) {
            Object *evaledSelf = Esther_eval(es, Tuple_get(ast, 1), context);
            return Object_call(es, evaledSelf, "new", Tuple_new(es, 0));
        } else {
            Object *newObject = Object_new(es);
            Esther_eval(es, Tuple_get(ast, 1), Context_childContext(context, newObject, Object_new(es)));
            return newObject;
        }
    } else if (id == id_function) {
        Object *array = Tuple_get(ast, 2);
        int argc = Array_size(array);

        const char **params = malloc(argc * sizeof(const char *));

        for (int i = 0; i < argc; i++)
            params[i] = strdup(String_c_str(Array_get(array, i)));

        Object *f = InterpretedFunction_new(es, String_c_str(Tuple_get(ast, 1)), argc, params, context, Tuple_get(ast, 3));

        free(params);

        return f;
    } else if (id == id_call) {
        Object *evaledSelf;
        Object *evaledF;

        Object *child = Tuple_get(ast, 1);
        Id childId = Symbol_getId(Tuple_get(child, 0));

        if (childId == id_attr) {
            evaledSelf = Esther_eval(es, Tuple_get(child, 1), context);
            evaledF = Object_resolve(evaledSelf, String_c_str(Tuple_get(child, 2)));
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
    } else if (id == id_id) {
        return Context_resolve(es, context, String_c_str(Tuple_get(ast, 1)));
    } else if (id == id_sharp) {
        Object *value = Tuple_get(ast, 1);

        if (Object_is(value, es->numericClass))
            return ValueObject_new_var(es, ValueObject_getValue(value));
        else if (Object_is(value, es->stringClass))
            return String_new(es, String_c_str(value));
    }

    return es->nullObject;
}
