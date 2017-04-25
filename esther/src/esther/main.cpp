#include <esther.h>

Object *print(Esther *esther, Object *self, Tuple *args) {
    printf("%s\n", String_c_str(Object_toString(esther, self)));
    printf("%s\n", String_c_str(Object_toString(esther, (Object *)args)));
    return self;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
    Esther e;
    Esther_init(&e);

    Class *_class = Class_new_init(&e, "A", NULL);

    Object *m = Object_new(&e);
    Object_setAttribute(m, "()", (Object *)Function_new(&e, "()", (Object * (*)())print, -1));

    Class_setMethod(_class, "m", m);

    Object *obj = Class_newInstance(&e, _class, Tuple_new(&e, 0));

    Object_call(&e, obj, "m", Tuple_new(&e, 2, String_new(&e, "arg1"), String_new(&e, "arg2")));

    Symbol *sBrace = Symbol_new(&e, "{}");
    Symbol *sClass = Symbol_new(&e, "class");
    Symbol *sEq = Symbol_new(&e, "=");
    Symbol *sSelf = Symbol_new(&e, "self");
    Symbol *sAttr = Symbol_new(&e, "attr");
    Symbol *sNew = Symbol_new(&e, "new");
    Symbol *sFunction = Symbol_new(&e, "function");
    Symbol *sCall = Symbol_new(&e, "call");
    Symbol *sId = Symbol_new(&e, "id");
    Symbol *sSharp = Symbol_new(&e, "#");

    Object *ast = (Object *)Tuple_new(&e, 2,
                                      sBrace,
                                      Array_new(&e, 3,
                                                Tuple_new(&e, 3,
                                                          sClass,
                                                          String_new(&e, "A"),
                                                          Tuple_new(&e, 3,
                                                                    sCall,
                                                                    Tuple_new(&e, 3,
                                                                              sAttr,
                                                                              Tuple_new(&e, 1,
                                                                                        sSelf),
                                                                              String_new(&e, "setMethod")),
                                                                    Array_new(&e, 2,
                                                                              Tuple_new(&e, 2,
                                                                                        sSharp,
                                                                                        String_new(&e, "m")),
                                                                              Tuple_new(&e, 2,
                                                                                        sNew,
                                                                                        Tuple_new(&e, 3,
                                                                                                  sEq,
                                                                                                  Tuple_new(&e, 3,
                                                                                                            sAttr,
                                                                                                            Tuple_new(&e, 1,
                                                                                                                      sSelf),
                                                                                                            String_new(&e, "()")),
                                                                                                  Tuple_new(&e, 4,
                                                                                                            sFunction,
                                                                                                            String_new(&e, ""),
                                                                                                            Array_new(&e, 2,
                                                                                                                      String_new(&e, "this"),
                                                                                                                      String_new(&e, "args")),
                                                                                                            Tuple_new(&e, 3,
                                                                                                                      sCall,
                                                                                                                      Tuple_new(&e, 3,
                                                                                                                                sAttr,
                                                                                                                                Tuple_new(&e, 2,
                                                                                                                                          sId,
                                                                                                                                          String_new(&e, "IO")),
                                                                                                                                String_new(&e, "writeLine")),
                                                                                                                      Array_new(&e, 2,
                                                                                                                                Tuple_new(&e, 2,
                                                                                                                                          sId,
                                                                                                                                          String_new(&e, "this")),
                                                                                                                                Tuple_new(&e, 2,
                                                                                                                                          sId,
                                                                                                                                          String_new(&e, "args")))))))))),
                                                Tuple_new(&e, 3,
                                                          sEq,
                                                          Tuple_new(&e, 2,
                                                                    sId,
                                                                    String_new(&e, "a")),
                                                          Tuple_new(&e, 3,
                                                                    sNew,
                                                                    Tuple_new(&e, 2,
                                                                              sId,
                                                                              String_new(&e, "A")),
                                                                    Array_new(&e, 0))),
                                                Tuple_new(&e, 3,
                                                          sCall,
                                                          Tuple_new(&e, 3,
                                                                    sAttr,
                                                                    Tuple_new(&e, 2,
                                                                              sId,
                                                                              String_new(&e, "a")),
                                                                    String_new(&e, "m")),
                                                          Array_new(&e, 2,
                                                                    Tuple_new(&e, 2,
                                                                              sSharp,
                                                                              String_new(&e, "arg1")),
                                                                    Tuple_new(&e, 2,
                                                                              sSharp,
                                                                              String_new(&e, "arg2"))))));

    printf("%s\n", String_c_str(Object_toString(&e, ast)));

    Esther_eval(&e, ast, e.root);

    return 0;
}
