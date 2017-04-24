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

    Object *obj = Class_newInstance(&e, _class, Tuple_new(&e));

    Object_call(&e, obj, "m", Tuple_new_init_va(&e, 2, String_new_init(&e, "arg1"), String_new_init(&e, "arg2")));

    Object *ast = (Object *)Tuple_new_init_va(&e, 2,
                                              Symbol_new(&e, "{}"),
                                              Array_new_init_va(&e, 3,
                                                                Tuple_new_init_va(&e, 3,
                                                                                  Symbol_new(&e, "class"),
                                                                                  String_new_init(&e, "A"),
                                                                                  Tuple_new_init_va(&e, 3,
                                                                                                    Symbol_new(&e, "="),
                                                                                                    Tuple_new_init_va(&e, 3,
                                                                                                                      Symbol_new(&e, "attr"),
                                                                                                                      Tuple_new_init_va(&e, 1,
                                                                                                                                        Symbol_new(&e, "self")),
                                                                                                                      String_new_init(&e, "m")),
                                                                                                    Tuple_new_init_va(&e, 2,
                                                                                                                      Symbol_new(&e, "new"),
                                                                                                                      Tuple_new_init_va(&e, 3,
                                                                                                                                        Symbol_new(&e, "="),
                                                                                                                                        Tuple_new_init_va(&e, 3,
                                                                                                                                                          Symbol_new(&e, "attr"),
                                                                                                                                                          Tuple_new_init_va(&e, 1,
                                                                                                                                                                            Symbol_new(&e, "self")),
                                                                                                                                                          String_new_init(&e, "()")),
                                                                                                                                        Tuple_new_init_va(&e, 4,
                                                                                                                                                          Symbol_new(&e, "function"),
                                                                                                                                                          String_new_init(&e, ""),
                                                                                                                                                          Array_new_init_va(&e, 2,
                                                                                                                                                                            String_new_init(&e, "this"),
                                                                                                                                                                            String_new_init(&e, "args")),
                                                                                                                                                          Tuple_new_init_va(&e, 3,
                                                                                                                                                                            Symbol_new(&e, "call"),
                                                                                                                                                                            Tuple_new_init_va(&e, 3,
                                                                                                                                                                                              Symbol_new(&e, "attr"),
                                                                                                                                                                                              Tuple_new_init_va(&e, 2,
                                                                                                                                                                                                                Symbol_new(&e, "id"),
                                                                                                                                                                                                                String_new_init(&e, "IO")),
                                                                                                                                                                                              String_new_init(&e, "writeLine")),
                                                                                                                                                                            Array_new_init_va(&e, 2,
                                                                                                                                                                                              Tuple_new_init_va(&e, 2,
                                                                                                                                                                                                                Symbol_new(&e, "id"),
                                                                                                                                                                                                                String_new_init(&e, "this")),
                                                                                                                                                                                              Tuple_new_init_va(&e, 2,
                                                                                                                                                                                                                Symbol_new(&e, "id"),
                                                                                                                                                                                                                String_new_init(&e, "args"))))))))),
                                                                Tuple_new_init_va(&e, 3,
                                                                                  Symbol_new(&e, "="),
                                                                                  Tuple_new_init_va(&e, 2,
                                                                                                    Symbol_new(&e, "id"),
                                                                                                    String_new_init(&e, "a")),
                                                                                  Tuple_new_init_va(&e, 3,
                                                                                                    Symbol_new(&e, "new"),
                                                                                                    Tuple_new_init_va(&e, 2,
                                                                                                                      Symbol_new(&e, "id"),
                                                                                                                      String_new_init(&e, "A")),
                                                                                                    Array_new(&e))),
                                                                Tuple_new_init_va(&e, 3,
                                                                                  Symbol_new(&e, "call"),
                                                                                  Tuple_new_init_va(&e, 3,
                                                                                                    Symbol_new(&e, "attr"),
                                                                                                    Tuple_new_init_va(&e, 2,
                                                                                                                      Symbol_new(&e, "id"),
                                                                                                                      String_new_init(&e, "a")),
                                                                                                    String_new_init(&e, "m")),
                                                                                  Array_new_init_va(&e, 2,
                                                                                                    Tuple_new_init_va(&e, 2,
                                                                                                                      Symbol_new(&e, "#"),
                                                                                                                      String_new_init(&e, "arg1")),
                                                                                                    Tuple_new_init_va(&e, 2,
                                                                                                                      Symbol_new(&e, "#"),
                                                                                                                      String_new_init(&e, "arg2"))))));

    printf("%s\n", String_c_str(Object_toString(&e, ast)));

    return 0;
}
