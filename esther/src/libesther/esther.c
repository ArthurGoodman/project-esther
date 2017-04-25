#include "esther/esther.h"

#include "esther/array.h"
#include "esther/class.h"
#include "esther/function.h"
#include "esther/object.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/valueobject.h"
#include "esther/std_map.h"
#include "esther/context.h"

static Object *ObjectClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return Object_new(esther);
}

static Object *ClassClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return (Object *)Class_new(esther);
}

static Object *StringClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return (Object *)String_new(esther, "");
}

static Object *SymbolClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return (Object *)Symbol_new(esther, "");
}

static Object *FunctionClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self), Tuple *UNUSED(args)) {
    return NULL;
}

static Object *TupleClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return (Object *)Tuple_new(esther, 0);
}

static Object *ArrayClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    return (Object *)Array_new(esther, 0);
}

static Object *BooleanClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self), Tuple *UNUSED(args)) {
    return NULL;
}

static Object *NullClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self), Tuple *UNUSED(args)) {
    return NULL;
}

static Object *NumericClass_virtual_newInstance(Esther *UNUSED(esther), Class *UNUSED(self), Tuple *UNUSED(args)) {
    return NULL;
}

static Object *CharClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *args) {
    if (Tuple_size(args) == 0)
        return (Object *)ValueObject_new_char(esther, '\0');

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), esther->numericClass))
            return NULL;

        return (Object *)ValueObject_new_char(esther, Variant_toChar(((ValueObject *)Tuple_get(args, 0))->value));
    }

    return NULL;
}

static Object *IntClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    if (Tuple_size(args) == 0)
        return (Object *)ValueObject_new_int(esther, 0);

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), esther->numericClass))
            return NULL;

        return (Object *)ValueObject_new_int(esther, Variant_toInt(((ValueObject *)Tuple_get(args, 0))->value));
    }

    return NULL;
}

static Object *FloatClass_virtual_newInstance(Esther *esther, Class *UNUSED(self), Tuple *UNUSED(args)) {
    if (Tuple_size(args) == 0)
        return (Object *)ValueObject_new_real(esther, 0.0);

    if (Tuple_size(args) == 1) {
        if (!Object_is(Tuple_get(args, 0), esther->numericClass))
            return NULL;

        return (Object *)ValueObject_new_real(esther, Variant_toReal(((ValueObject *)Tuple_get(args, 0))->value));
    }

    return NULL;
}

static String *True_virtual_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new(esther, "true");
}

static String *False_virtual_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new(esther, "false");
}

static bool False_virtual_isTrue() {
    return false;
}

static String *Null_virtual_toString(Esther *esther, Object *UNUSED(self)) {
    return String_new(esther, "null");
}

static Object *ObjectClass_class(Esther *UNUSED(esther), Object *self) {
    return (Object *)Object_getClass(self);
}

static Object *ObjectClass_equals(Esther *esther, Object *self, Object *obj) {
    return Esther_toBoolean(esther, Object_equals(esther, self, obj));
}

static Object *ClassClass_superclass(Esther *UNUSED(esther), Object *self) {
    return (Object *)Class_getSuperclass((Class *)self);
}

static Object *ClassClass_hasMethod(Esther *esther, Class *self, String *name) {
    return Esther_toBoolean(esther, Class_hasMethod(self, String_c_str(name)));
}

static Object *ClassClass_getMethod(Esther *UNUSED(esther), Class *self, String *name) {
    return Class_getMethod(self, String_c_str(name));
}

static Object *ClassClass_setMethod(Esther *UNUSED(esther), Class *self, String *name, Object *method) {
    Class_setMethod(self, String_c_str(name), method);
    return method;
}

static Object *NumericClass_add(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_add(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_sub(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_sub(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_mul(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_mul(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_div(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_div(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_mod(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_mod(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_pow(Esther *esther, ValueObject *a, ValueObject *b) {
    return (Object *)ValueObject_new_var(esther, Variant_pow(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_lt(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_lt(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_gt(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_gt(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_lte(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_lte(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_gte(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_gte(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_eq(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_eq(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *NumericClass_ne(Esther *esther, ValueObject *a, ValueObject *b) {
    return Esther_toBoolean(esther, Variant_ne(ValueObject_getValue(a), ValueObject_getValue(b)));
}

static Object *IO_write(Esther *esther, Object *self, Tuple *args) {
    if (Tuple_size(args) == 0)
        printf("%s", String_c_str(Object_toString(esther, self)));
    else
        for (size_t i = 0; i < Tuple_size(args); i++)
            printf("%s", String_c_str(Object_toString(esther, Tuple_get(args, i))));

    return esther->nullObject;
}

static Object *IO_writeLine(Esther *esther, Object *self, Tuple *args) {
    if (Tuple_size(args) == 0)
        printf("%s\n", String_c_str(Object_toString(esther, self)));
    else
        for (size_t i = 0; i < Tuple_size(args); i++)
            printf("%s\n", String_c_str(Object_toString(esther, Tuple_get(args, i))));

    return esther->nullObject;
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

    self->charClass = Class_new_init(self, "Char", self->numericClass);
    self->charClass->newInstance = CharClass_virtual_newInstance;

    self->intClass = Class_new_init(self, "Int", self->numericClass);
    self->intClass->newInstance = IntClass_virtual_newInstance;

    self->floatClass = Class_new_init(self, "Float", self->numericClass);
    self->floatClass->newInstance = FloatClass_virtual_newInstance;

    self->trueObject = Object_new(self);
    self->trueObject->objectClass = self->booleanClass;
    self->trueObject->toString = self->trueObject->inspect = True_virtual_toString;

    self->falseObject = Object_new(self);
    self->falseObject->objectClass = self->booleanClass;
    self->falseObject->toString = self->falseObject->inspect = False_virtual_toString;
    self->falseObject->isTrue = False_virtual_isTrue;

    self->nullObject = Object_new(self);
    self->nullObject->objectClass = self->nullClass;
    self->nullObject->toString = self->nullObject->inspect = Null_virtual_toString;
    self->nullObject->isTrue = False_virtual_isTrue;

    Class_setMethod_func(self->objectClass, Function_new(self, "class", (Object * (*)())ObjectClass_class, 0));
    Class_setMethod_func(self->objectClass, Function_new(self, "toString", (Object * (*)())Object_toString, 0));
    Class_setMethod_func(self->objectClass, Function_new(self, "inspect", (Object * (*)())Object_inspect, 0));
    Class_setMethod_func(self->objectClass, Function_new(self, "equals", (Object * (*)())ObjectClass_equals, 1));
    Class_setMethod(self->objectClass, "==", Class_getMethod(self->objectClass, "equals"));

    Class_setMethod_func(self->classClass, Function_new(self, "superclass", (Object * (*)())ClassClass_superclass, 0));
    Class_setMethod_func(self->classClass, Function_new(self, "new", (Object * (*)())Class_newInstance, -1));
    Class_setMethod(self->classClass, "()", Class_getMethod(self->classClass, "new"));
    Class_setMethod_func(self->classClass, Function_new(self, "hasMethod", (Object * (*)())ClassClass_hasMethod, 1));
    Class_setMethod_func(self->classClass, Function_new(self, "getMethod", (Object * (*)())ClassClass_getMethod, 1));
    Class_setMethod_func(self->classClass, Function_new(self, "setMethod", (Object * (*)())ClassClass_setMethod, 2));

    Class_setMethod_func(self->numericClass, Function_new(self, "+", (Object * (*)())NumericClass_add, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "-", (Object * (*)())NumericClass_sub, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "*", (Object * (*)())NumericClass_mul, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "/", (Object * (*)())NumericClass_div, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "%", (Object * (*)())NumericClass_mod, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "^", (Object * (*)())NumericClass_pow, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "<", (Object * (*)())NumericClass_lt, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, ">", (Object * (*)())NumericClass_gt, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "<=", (Object * (*)())NumericClass_lte, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, ">=", (Object * (*)())NumericClass_gte, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "==", (Object * (*)())NumericClass_eq, 1));
    Class_setMethod_func(self->numericClass, Function_new(self, "!=", (Object * (*)())NumericClass_ne, 1));

    self->mainObject = Object_new(self);

    self->io = Object_new(self);

    Object_setAttribute(self->io, "write", (Object *)Function_new(self, "write", (Object * (*)())IO_write, -1));
    Object_setAttribute(self->io, "writeLine", (Object *)Function_new(self, "writeLine", (Object * (*)())IO_writeLine, -1));

    self->root = Context_new(self);

    self->rootObjects = std_map_new(string_compare);

    Esther_setRootObject(self, "Object", (Object *)self->objectClass);
    Esther_setRootObject(self, "Class", (Object *)self->classClass);
    Esther_setRootObject(self, "String", (Object *)self->stringClass);
    Esther_setRootObject(self, "Symbol", (Object *)self->symbolClass);
    Esther_setRootObject(self, "Function", (Object *)self->functionClass);
    Esther_setRootObject(self, "Tuple", (Object *)self->tupleClass);
    Esther_setRootObject(self, "Array", (Object *)self->arrayClass);
    Esther_setRootObject(self, "Boolean", (Object *)self->booleanClass);
    Esther_setRootObject(self, "Null", (Object *)self->nullClass);
    Esther_setRootObject(self, "Numeric", (Object *)self->numericClass);
    Esther_setRootObject(self, "Char", (Object *)self->charClass);
    Esther_setRootObject(self, "Int", (Object *)self->intClass);
    Esther_setRootObject(self, "Float", (Object *)self->floatClass);

    Esther_setRootObject(self, "IO", self->io);
}

Object *Esther_toBoolean(Esther *self, bool value) {
    return value ? self->trueObject : self->falseObject;
}

bool Esther_hasRootObject(Esther *self, const char *name) {
    return std_map_contains(self->rootObjects, name);
}

Object *Esther_getRootObject(Esther *self, const char *name) {
    return (Object *)std_map_get(self->rootObjects, name);
}

void Esther_setRootObject(Esther *self, const char *name, Object *value) {
    std_map_set(self->rootObjects, name, value);
}

Object *Esther_eval(Esther *self, Object *ast, Context *context) {
    Tuple *t = (Tuple *)ast;

    if (Tuple_size(t) == 0)
        return self->nullObject;

    const char *str = idToString(Symbol_getId((Symbol *)Tuple_get(t, 0)));

    if (strcmp(str, "{}") == 0) {
        Array *nodes = (Array *)Tuple_get(t, 1);

        Object *value = self->nullObject;

        for (size_t i = 0; i < Array_size(nodes); i++)
            value = Esther_eval(self, Array_get(nodes, i), context);

        return value;
    } else if (strcmp(str, "class") == 0) {
        const char *name = String_c_str((String *)Tuple_get(t, 1));
        Class *_class = Class_new_init(self, name, NULL);

        Context *child = Context_childContext(context, (Object *)_class, Object_new(self));
        Esther_eval(self, Tuple_get(t, 2), child);

        if (strlen(name) > 0)
            Context_setLocal(context, name, (Object *)_class);

        return (Object *)_class;
    } else if (strcmp(str, "=") == 0) {
        Tuple *f = (Tuple *)Tuple_get(t, 1);
        const char *sym = idToString(Symbol_getId((Symbol *)Tuple_get(f, 0)));

        Object *value = Esther_eval(self, Tuple_get(t, 2), context);

        if (strcmp(sym, "attr") == 0) {
            Object *evaledSelf = Esther_eval(self, Tuple_get(f, 1), context);
            Object_setAttribute(evaledSelf, String_c_str((String *)Tuple_get(f, 2)), value);
        } else if (strcmp(sym, "id") == 0) {
            const char *name = String_c_str((String *)Tuple_get(f, 1));

            if (!Context_assign(context, name, value))
                Context_setLocal(context, name, value);
        } else
            return NULL;

        return value;
    } else if (strcmp(str, "self") == 0) {
        return Context_getSelf(context);
    } else if (strcmp(str, "attr") == 0) {
        Object *evaledSelf = Esther_eval(self, Tuple_get(t, 1), context);
        return Object_getAttribute(evaledSelf, String_c_str((String *)Tuple_get(t, 2)));
    } else if (strcmp(str, "new") == 0) {
        if (Tuple_size(t) == 3) {
            Object *evaledSelf = Esther_eval(self, Tuple_get(t, 1), context);
            return Object_call(self, evaledSelf, "new", Tuple_new(self, 0));
        } else {
            Object *newObject = Object_new(self);
            Esther_eval(self, Tuple_get(t, 1), Context_childContext(context, newObject, Object_new(self)));
            return newObject;
        }
    } else if (strcmp(str, "function") == 0) {
        Array *array = (Array *)Tuple_get(t, 2);
        int argc = Array_size(array);

        const char **params = malloc(argc * sizeof(const char *));

        for (int i = 0; i < argc; i++)
            params[i] = strdup(String_c_str((String *)Array_get(array, i)));

        Function *f = InterpretedFunction_new(self, String_c_str((String *)Tuple_get(t, 1)), argc, params, context, Tuple_get(t, 3));

        free(params);

        return (Object *)f;
    } else if (strcmp(str, "call") == 0) {
        Object *evaledSelf = NULL;
        Object *evaledF = NULL;

        Tuple *f = (Tuple *)Tuple_get(t, 1);
        const char *sym = idToString(Symbol_getId((Symbol *)Tuple_get(f, 0)));

        if (strcmp(sym, "attr") == 0) {
            evaledSelf = Esther_eval(self, Tuple_get(f, 1), context);
            evaledF = Object_resolve(evaledSelf, String_c_str((String *)Tuple_get(f, 2)));
        } else if (strcmp(sym, ".") == 0) {
            evaledSelf = Esther_eval(self, Tuple_get(f, 1), context);
            evaledF = Esther_eval(self, Tuple_get(f, 2), Context_childContext(context, evaledSelf, Object_new(self)));
        } else {
            evaledSelf = Context_getSelf(context);
            evaledF = Esther_eval(self, (Object *)f, context);
        }

        Array *args = (Array *)Tuple_get(t, 2);

        Tuple *evaledArgs = Tuple_new_init_null(self, Array_size(args));

        for (size_t i = 0; i < Array_size(args); i++)
            Tuple_set(evaledArgs, i, Esther_eval(self, Array_get(args, i), context));

        return Object_call_function(self, evaledSelf, evaledF, evaledArgs);
    } else if (strcmp(str, "id") == 0) {
        return Context_resolve(self, context, String_c_str((String *)Tuple_get(t, 1)));
    } else if (strcmp(str, "#") == 0) {
        Object *value = Tuple_get(t, 1);

        if (Object_is(value, self->numericClass))
            return (Object *)ValueObject_new_var(self, ValueObject_getValue((ValueObject *)value));
        else if (Object_is(value, self->stringClass))
            return (Object *)String_new(self, String_c_str((String *)value));
        else
            return NULL;
    }

    return self->nullObject;
}
