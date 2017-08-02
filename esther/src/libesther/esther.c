#include "esther/esther.h"

#if defined(__linux)
#include <dlfcn.h>
#include <unistd.h>
#elif defined(__WIN32)
#include <windows.h>
#endif

#include "ast.h"
#include "core.h"
#include "esther/array.h"
#include "esther/class.h"
#include "esther/context.h"
#include "esther/exception.h"
#include "esther/function.h"
#include "esther/lexer.h"
#include "esther/map.h"
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

typedef struct GlobalMapper {
    Mapper base;

    Esther *es;
} GlobalMapper;

static void GlobalMapper_mapOnRefs(GlobalMapper *self, MapFunction f) {
    std_map_iterator i;
    std_map_begin(self->es->rootObjects, &i);

    while (!std_map_end(self->es->rootObjects, &i)) {
        f(std_map_iterator_value(&i));
        std_map_iterator_next(&i);
    }

    f(self->es->trueObject);
    f(self->es->falseObject);
    f(self->es->nullObject);

    f(self->es->lexer);
    f(self->es->parser);

    f(self->es->mainObject);
    f(self->es->esther);

    f(self->es->root);

    f(self->es->modules);

#define X(a, b) f(sym_##a);
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X

    for (struct FileRecord *rec = self->es->file; rec; rec = rec->next)
        f(rec->source);
}

static MapperVTable vtable_for_GlobalMapper = {
    .mapOnRefs = (void (*)(Mapper *, MapFunction)) GlobalMapper_mapOnRefs
};

static Mapper *GlobalMapper_new(Esther *es) {
    GlobalMapper *self = malloc(sizeof(GlobalMapper));
    self->es = es;
    *(void **) self = &vtable_for_GlobalMapper;
    return (Mapper *) self;
}

static Object *Esther_print(Esther *es, Object *self, Object *args) {
    if (Tuple_size(args) == 0)
        printf("%s", String_c_str(Object_toString(es, self)));
    else
        for (size_t i = 0; i < Tuple_size(args); i++)
            printf("%s", String_c_str(Object_toString(es, Tuple_get(args, i))));

    return es->nullObject;
}

static Object *Esther_println(Esther *es, Object *self, Object *args) {
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

static void Esther_loadModules(Esther *es) {
    struct string str = executable_dir();
    string_append_c_str(&str, "modules.es");
    es->modules = Esther_evalFile(es, str.data);
    string_free(str);
}

void Esther_init(Esther *es) {
    gc_registerMapper(es->globalMapper = GlobalMapper_new(es));

    es->trueObject = NULL;
    es->falseObject = NULL;
    es->nullObject = NULL;

    es->lexer = NULL;
    es->parser = NULL;

    es->mainObject = NULL;
    es->esther = NULL;

    es->root = NULL;

    es->modules = NULL;

    es->file = NULL;

    es->rootObjects = std_map_new(compare_id);

    Core_initialize(es);

    es->lexer = Lexer_new(es);

    Object_setAttribute(es->lexer, c_str_to_id("lex"), Function_new(es, string_const("lex"), (Object * (*) ()) Lexer_lex, 1));

    es->parser = Parser_new(es);

    Object_setAttribute(es->parser, c_str_to_id("parse"), Function_new(es, string_const("parse"), (Object * (*) ()) Parser_parse, 1));

    es->mainObject = Object_new(es);

    es->esther = Object_new(es);

    Object_setAttribute(es->esther, c_str_to_id("lexer"), es->lexer);
    Object_setAttribute(es->esther, c_str_to_id("parser"), es->parser);
    Object_setAttribute(es->esther, c_str_to_id("eval"), Function_new(es, string_const("eval"), (Object * (*) ()) Esther_evalFunction, 1));

    es->root = Context_new(es);

    Context_setLocal(es->root, c_str_to_id("print"), Function_new(es, string_const("print"), (Object * (*) ()) Esther_print, -1));
    Context_setLocal(es->root, c_str_to_id("println"), Function_new(es, string_const("println"), (Object * (*) ()) Esther_println, -1));

    Esther_setRootObject(es, c_str_to_id("esther"), es->esther);

    init_identifiers(es);

    es->moduleHandles = std_map_new(compare_id);
    Esther_loadModules(es);
}

//@TODO: Think about what actually needs to be done during finalization
void Esther_finalize(Esther *es) {
    gc_finalize();

    free(es->globalMapper);

    std_map_iterator i;
    std_map_begin(es->moduleHandles, &i);

    while (!std_map_end(es->moduleHandles, &i)) {
        Esther_unloadModule(es, id_to_str((ID) std_map_iterator_key(&i)).data, std_map_iterator_value(&i));
        std_map_iterator_next(&i);
    }
}

Object *Esther_toBoolean(Esther *es, bool value) {
    return value ? es->trueObject : es->falseObject;
}

bool Esther_hasRootObject(Esther *es, ID name) {
    return std_map_contains(es->rootObjects, (void *) name);
}

Object *Esther_getRootObject(Esther *es, ID name) {
    return std_map_get(es->rootObjects, (void *) name);
}

void Esther_setRootObject(Esther *es, ID name, Object *value) {
    std_map_set(es->rootObjects, (void *) name, value);
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

    ID id = Symbol_getId(Expression_id(ast));

    Object *value = es->nullObject;

    TRY {
        if (id == id_braces) {
            Object *nodes = BlockExpression_nodes(ast);

            for (size_t i = 0; i < Array_size(nodes); i++)
                value = Esther_eval(es, Array_get(nodes, i), context);
        }

        else if (id == id_class) {
            struct string name = String_value(ClassExpression_name(ast));

            Object *superclass = Tuple_size(ast) == 4 ? Esther_eval(es, ClassExpression_superclass(ast), context) : NULL;

            Object *_class = Class_new(es, name, superclass);

            if (name.size > 0)
                Context_setLocal(context, str_to_id(name), _class);

            Esther_eval(es, ClassExpression_body(ast), Context_childContext(context, _class, Object_new(es)));

            value = _class;
        }

        else if (id == id_assign) {
            Object *child = BinaryExpression_left(ast);
            ID childId = Symbol_getId(Expression_id(child));

            value = Esther_eval(es, BinaryExpression_right(ast), context);

            if (childId == id_attr)
                Object_setAttribute(Esther_eval(es, AttributeExpression_self(child), context), str_to_id(String_value(AttributeExpression_name(child))), value);
            else if (childId == id_id) {
                struct string name = String_value(IdExpression_name(child));

                if (!Context_assign(context, str_to_id(name), value))
                    Context_setLocal(context, str_to_id(name), value);
            } else
                Exception_throw_new(es, "invalid assignment");
        }

        else if (id == id_plus) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("+"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_plusAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("+="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_minus) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("-"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_minusAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("-="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_multiply) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("*"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_multiplyAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("*="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_divide) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("/"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_divideAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("/="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_mod) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("%"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_modAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("%="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_power) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("**"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_powerAssign) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("**="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        }

        else if (id == id_lt) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("<"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_gt) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id(">"), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_le) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("<="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_ge) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id(">="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_eq) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("=="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        } else if (id == id_ne) {
            Object *left = Esther_eval(es, BinaryExpression_left(ast), context);
            value = Object_call(es, left, c_str_to_id("!="), 1, Esther_eval(es, BinaryExpression_right(ast), context));
        }

        else if (id == id_or) {
            value = Esther_toBoolean(es, Object_isTrue(Esther_eval(es, BinaryExpression_left(ast), context)) || Object_isTrue(Esther_eval(es, BinaryExpression_right(ast), context)));
        } else if (id == id_and) {
            value = Esther_toBoolean(es, Object_isTrue(Esther_eval(es, BinaryExpression_left(ast), context)) && Object_isTrue(Esther_eval(es, BinaryExpression_right(ast), context)));
        }

        else if (id == id_if) {
            if (Object_isTrue(Esther_eval(es, IfExpression_condition(ast), context)))
                value = Esther_eval(es, IfExpression_body(ast), context);
            else if (Tuple_size(ast) == 4)
                value = Esther_eval(es, IfExpression_elseBody(ast), context);
            else
                value = es->nullObject;
        }

        else if (id == id_while) {
            Object *condition = WhileExpression_condition(ast);
            Object *body = WhileExpression_body(ast);

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
            Object *nodes = TupleExpression_args(ast);
            value = Tuple_new_init_null(es, Array_size(nodes));

            for (size_t i = 0; i < Array_size(nodes); i++)
                Tuple_set(value, i, Esther_eval(es, Array_get(nodes, i), context));
        }

        else if (id == id_brackets) {
            Object *nodes = ArrayExpression_args(ast);
            value = Array_new(es, 0);

            for (size_t i = 0; i < Array_size(nodes); i++)
                Array_push(value, Esther_eval(es, Array_get(nodes, i), context));
        }

        else if (id == id_doubleArrow) {
            Object *nodes = MapExpression_args(ast);
            value = Map_new(es);

            for (size_t i = 0; i < Array_size(nodes); i++)
                Map_set(value, Esther_eval(es, Tuple_get(Array_get(nodes, i), 0), context), Esther_eval(es, Tuple_get(Array_get(nodes, i), 1), context));
        }

        else if (id == id_attr) {
            Object *evaledSelf = Esther_eval(es, AttributeExpression_self(ast), context);
            struct string name = String_value(AttributeExpression_name(ast));
            value = Object_resolve(evaledSelf, str_to_id(name));

            if (!value)
                Exception_throw_new(es, "undefined attribute '%s'", name.data);
        }

        else if (id == id_new) {
            if (Tuple_size(ast) == 2) {
                Object *newObject = Object_new(es);
                Esther_eval(es, NewExpression_body(ast), Context_childContext(context, newObject, Object_new(es)));
                value = newObject;
            } else if (Tuple_size(ast) == 4) {
                struct string name = String_value(NewExpression_name(ast));
                Object *evaledSelf = Context_resolve(es, context, str_to_id(name));

                if (!evaledSelf)
                    Exception_throw_new(es, "undefined variable '%s'", name.data);

                Object *args = NewExpression_args(ast);
                Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

                for (size_t i = 0; i < Array_size(args); i++)
                    Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

                Object *instance = Object_call_args(es, evaledSelf, c_str_to_id("new"), evaledArgs);

                Esther_eval(es, NewExpression_body(ast), Context_childContext(context, instance, Object_new(es)));

                value = instance;
            } else
                value = NULL;
        }

        else if (id == id_function) {
            struct string name = String_value(FunctionExpression_name(ast));
            Object *f = InterpretedFunction_new(es, name, FunctionExpression_params(ast), context, FunctionExpression_body(ast));

            if (name.size > 0) {
                Context_setLocal(context, str_to_id(name), f);

                Object *self = Context_getSelf(context);

                if (Object_getType(self) == TClass)
                    Class_setMethod(self, str_to_id(name), f);
            }

            value = f;
        }

        else if (id == id_call) {
            Object *evaledSelf;
            Object *evaledF;

            Object *child = CallExpression_self(ast);
            ID childId = Symbol_getId(Expression_id(child));

            if (childId == id_attr) {
                struct string name = String_value(AttributeExpression_name(child));

                evaledSelf = Esther_eval(es, AttributeExpression_self(child), context);
                evaledF = Object_resolve(evaledSelf, str_to_id(name));

                if (!evaledF)
                    Exception_throw_new(es, "undefined attribute '%s'", name.data);
            } else if (childId == id_dot) {
                evaledSelf = Esther_eval(es, DotExpression_self(child), context);
                evaledF = Esther_eval(es, DotExpression_body(child), Context_childContext(context, evaledSelf, Object_new(es)));
            } else {
                evaledSelf = Context_getSelf(context);
                evaledF = Esther_eval(es, child, context);
            }

            Object *args = CallExpression_args(ast);

            Object *evaledArgs = Tuple_new_init_null(es, Array_size(args));

            for (size_t i = 0; i < Array_size(args); i++)
                Tuple_set(evaledArgs, i, Esther_eval(es, Array_get(args, i), context));

            value = Object_callFunction(es, evaledSelf, evaledF, evaledArgs);
        }

        else if (id == id_id) {
            struct string name = String_value(IdExpression_name(ast));
            value = Context_resolve(es, context, str_to_id(name));

            if (!value)
                Exception_throw_new(es, "undefined variable '%s'", name.data);
        }

        else if (id == id_var) {
            struct string name = String_value(VarExpression_name(ast));
            value = Tuple_size(ast) == 3 ? Esther_eval(es, VarExpression_value(ast), context) : es->nullObject;

            Context_setLocal(context, str_to_id(name), value);
        }

        else if (id == id_dot) {
            Object *evaledSelf = Esther_eval(es, DotExpression_self(ast), context);
            value = Esther_eval(es, DotExpression_body(ast), Context_childContext(context, evaledSelf, Object_new(es)));
        }

        else if (id == id_sharp) {
            value = ValueExpression_value(ast);

            if (Object_getType(value) == TValueObject)
                value = ValueObject_new_var(es, ValueObject_getValue(value));
            else if (Object_getType(value) == TString)
                value = String_new(es, String_value(value));
        }

        else if (id == id_colon) {
            value = str_to_sym(es, String_value(SymbolExpression_name(ast)));
        }

        else if (id == id_not) {
            value = Esther_toBoolean(es, !Object_isTrue(Esther_eval(es, UnaryExpression_arg(ast), context)));
        }

        else if (id == id_import) {
            value = Esther_importModule(es, context, String_value(ImportExpression_name(ast)).data);
        }
    }
    CATCH(e) {
        if (!Exception_getPos(e) && Expression_hasPosition(ast))
            Exception_setPos(e, Expression_getPosition(ast));

        Exception_throw(e);
    }
    ENDTRY;

    return value;
}

static Object *evalFile(Esther *es, const char *fileName, Object *(*codeRunner)(Esther *, Object *) ) {
    struct FileRecord rec;

    rec.fileName = full_path(fileName);
    rec.source = NULL;
    rec.next = es->file;

    es->file = &rec;

    Object *value = es->nullObject;

    TRY {
        struct string rawCode = read_file(fileName);

        if (!rawCode.data) {
            printf("error: unable to read file\n");
            pop_jump_buffer();
            break;
        }

        Object *code = String_new_move(es, string_expand_tabs(rawCode));

        es->file->source = code;

        string_free(rawCode);

        value = codeRunner(es, code);
    }
    CATCH(e) {
        Object *pos = Exception_getPos(e);

        if (pos != NULL && es->file && es->file->source) {
            int offset = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 0)));
            int line = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 1)));
            int column = Variant_toInt(ValueObject_getValue(Tuple_get(pos, 2)));

            struct string q = string_quote(String_value(es->file->source), offset, column);
            printf("%s:%i:%i: error: %s\n%s\n", es->file->fileName, line, column, Exception_getMessage(e).data, q.data);
            string_free(q);
        } else
            printf("error: %s\n", Exception_getMessage(e).data);
    }
    ENDTRY;

    free((void *) es->file->fileName);

    es->file = es->file->next;

    return value;
}

static Object *runCodeSilently(Esther *es, Object *code) {
    return Esther_eval(es, Parser_parse(es, es->parser, Lexer_lex(es, es->lexer, code)), es->root);
}

static Object *runCode(Esther *es, Object *code) {
    Object *tokens = Lexer_lex(es, es->lexer, code);
    Object_setAttribute(es->esther, c_str_to_id("tokens"), tokens);

    // Esther_println(es, tokens, Tuple_new(es, 0));

    Object *ast = Parser_parse(es, es->parser, tokens);
    Object_setAttribute(es->esther, c_str_to_id("ast"), ast);

    // Esther_println(es, ast, Tuple_new(es, 0));

    Object *value = Esther_eval(es, ast, es->root);

    printf("=> %s\n", String_c_str(Object_inspect(es, value)));

    return value;
}

void Esther_runScript(Esther *es, const char *fileName) {
    evalFile(es, fileName, runCode);
}

Object *Esther_evalFile(Esther *es, const char *fileName) {
    return evalFile(es, fileName, runCodeSilently);
}

//@Refactor module loading system (and these two functions in particular)
//@TODO: Make modules into singletons
Object *Esther_importModule(Esther *es, Context *context, const char *name) {
    Object *strName = String_new_c_str(es, name);

    if (!Map_contains(es->modules, strName))
        Exception_throw_new(es, "cannot find module named '%s'", name);

    struct string path = executable_dir();
    string_append(&path, String_value(Map_get(Map_get(es->modules, strName), c_str_to_sym(es, "path"))));

#if defined(__linux)
    string_append_c_str(&path, ".so");
#elif defined(__WIN32)
    string_append_c_str(&path, ".dll");
#endif

    const char *real_path = full_path(path.data);

#if defined(__linux)
    void *library = dlopen(real_path, RTLD_LAZY);
#elif defined(__WIN32)
    HINSTANCE library = LoadLibraryA(real_path);
#endif

    std_map_set(es->moduleHandles, (void *) c_str_to_id(name), library);

    string_free(path);
    free((void *) real_path);

    if (!library)
#if defined(__linux)
        Exception_throw_new(es, dlerror());
#elif defined(__WIN32)
        Exception_throw_new(es, "unable to load library, error code: %i", GetLastError());
#endif

#if defined(__linux)
    dlerror();
#endif

    struct string initializeFunctionName = string_new_c_str(name);
    string_append_c_str(&initializeFunctionName, "_initialize");

#if defined(__linux)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    void (*initialize)(Esther *, Context *) = dlsym(library, initializeFunctionName.data);
#pragma GCC diagnostic pop
#elif defined(__WIN32)
    void (*initialize)(Esther *, Context *) = (void (*)(Esther *, Context *)) GetProcAddress(library, initializeFunctionName.data);
#endif

    string_free(initializeFunctionName);

#if defined(__linux)
    char *error;
    if ((error = dlerror()))
        Exception_throw_new(es, error);
#elif defined(__WIN32)
    if (!initialize)
        Exception_throw_new(es, "unable to load initialize function");
#endif

    initialize(es, context);

    return es->nullObject;
}

//@Fix: Exceptions here are not caught
void Esther_unloadModule(Esther *es, const char *name, void *library) {
    struct string finalizeFunctionName = string_new_c_str(name);
    string_append_c_str(&finalizeFunctionName, "_finalize");

#if defined(__linux)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    void (*finalize)(Esther *) = dlsym(library, finalizeFunctionName.data);
#pragma GCC diagnostic pop
#elif defined(__WIN32)
    void (*finalize)(Esther *) = (void (*)(Esther *)) GetProcAddress(library, finalizeFunctionName.data);
#endif

    string_free(finalizeFunctionName);

#if defined(__linux)
    char *error;
    if ((error = dlerror()))
        Exception_throw_new(es, error);
#elif defined(__WIN32)
    if (!finalize)
        Exception_throw_new(es, "unable to load finalize function");
#endif

    finalize(es);

#if defined(__linux)
    dlclose(library);
#elif defined(__WIN32)
    FreeLibrary(library);
#endif
}
