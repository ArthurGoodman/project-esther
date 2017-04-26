#include <esther.h>

Object *print(Esther *esther, Object *self, Object *args) {
    printf("%s\n", String_c_str(Object_toString(esther, self)));
    printf("%s\n", String_c_str(Object_toString(esther, args)));
    return self;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
    Esther e;
    Esther_init(&e);

    Object *_class = Class_new_init(&e, "A", NULL);

    Object *m = Object_new(&e);
    Object_setAttribute(m, "()", Function_new(&e, "()", (Object * (*)())print, -1));

    Class_setMethod(_class, "m", m);

    Object *obj = Class_newInstance(&e, _class, Tuple_new(&e, 0));

    Object_call(&e, obj, "m", Tuple_new(&e, 2, String_new(&e, "arg1"), String_new(&e, "arg2")));

    Object *symBrace = Symbol_new(&e, "{}");
    Object *symClass = Symbol_new(&e, "class");
    Object *symEq = Symbol_new(&e, "=");
    Object *symSelf = Symbol_new(&e, "self");
    Object *symAttr = Symbol_new(&e, "attr");
    Object *symNew = Symbol_new(&e, "new");
    Object *symFunction = Symbol_new(&e, "function");
    Object *symCall = Symbol_new(&e, "call");
    Object *symId = Symbol_new(&e, "id");
    Object *symSharp = Symbol_new(&e, "#");

    Object *ast = Tuple_new(&e, 2,
                            symBrace,
                            Array_new(&e, 3,
                                      Tuple_new(&e, 3,
                                                symClass,
                                                String_new(&e, "A"),
                                                Tuple_new(&e, 3,
                                                          symCall,
                                                          Tuple_new(&e, 3,
                                                                    symAttr,
                                                                    Tuple_new(&e, 1,
                                                                              symSelf),
                                                                    String_new(&e, "setMethod")),
                                                          Array_new(&e, 2,
                                                                    Tuple_new(&e, 2,
                                                                              symSharp,
                                                                              String_new(&e, "m")),
                                                                    Tuple_new(&e, 2,
                                                                              symNew,
                                                                              Tuple_new(&e, 3,
                                                                                        symEq,
                                                                                        Tuple_new(&e, 3,
                                                                                                  symAttr,
                                                                                                  Tuple_new(&e, 1,
                                                                                                            symSelf),
                                                                                                  String_new(&e, "()")),
                                                                                        Tuple_new(&e, 4,
                                                                                                  symFunction,
                                                                                                  String_new(&e, ""),
                                                                                                  Array_new(&e, 2,
                                                                                                            String_new(&e, "this"),
                                                                                                            String_new(&e, "args")),
                                                                                                  Tuple_new(&e, 3,
                                                                                                            symCall,
                                                                                                            Tuple_new(&e, 3,
                                                                                                                      symAttr,
                                                                                                                      Tuple_new(&e, 2,
                                                                                                                                symId,
                                                                                                                                String_new(&e, "IO")),
                                                                                                                      String_new(&e, "writeLine")),
                                                                                                            Array_new(&e, 2,
                                                                                                                      Tuple_new(&e, 2,
                                                                                                                                symId,
                                                                                                                                String_new(&e, "this")),
                                                                                                                      Tuple_new(&e, 2,
                                                                                                                                symId,
                                                                                                                                String_new(&e, "args")))))))))),
                                      Tuple_new(&e, 3,
                                                symEq,
                                                Tuple_new(&e, 2,
                                                          symId,
                                                          String_new(&e, "a")),
                                                Tuple_new(&e, 3,
                                                          symNew,
                                                          Tuple_new(&e, 2,
                                                                    symId,
                                                                    String_new(&e, "A")),
                                                          Array_new(&e, 0))),
                                      Tuple_new(&e, 3,
                                                symCall,
                                                Tuple_new(&e, 3,
                                                          symAttr,
                                                          Tuple_new(&e, 2,
                                                                    symId,
                                                                    String_new(&e, "a")),
                                                          String_new(&e, "m")),
                                                Array_new(&e, 2,
                                                          Tuple_new(&e, 2,
                                                                    symSharp,
                                                                    String_new(&e, "arg1")),
                                                          Tuple_new(&e, 2,
                                                                    symSharp,
                                                                    String_new(&e, "arg2"))))));

    printf("%s\n", String_c_str(Object_toString(&e, ast)));

    Esther_eval(&e, ast, e.root);

    return 0;
}
