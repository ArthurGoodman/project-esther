#include <esther.h>

Object *print(Esther *es, Object *self, Object *_this, Object *args) {
    printf("%s\n", String_c_str(Object_toString(es, _this)));
    printf("%s\n", String_c_str(Object_toString(es, args)));
    return self;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
    TRY {
        Esther es;
        Esther_init(&es);

        Object *_class = Class_new_init(&es, "A", NULL);

        Object *m = Object_new(&es);
        Object_setAttribute(m, "()", Function_new(&es, "()", (Object * (*)()) print, 2));

        Class_setMethod(_class, "m", m);

        Object *obj = Class_newInstance(&es, _class, Tuple_new(&es, 0));

        Object_call(&es, obj, "m", Tuple_new(&es, 2, String_new(&es, "arg1"), String_new(&es, "arg2")));

        Object *symBraces = Symbol_new(&es, "{}");
        Object *symClass = Symbol_new(&es, "class");
        Object *symAssign = Symbol_new(&es, "=");
        Object *symSelf = Symbol_new(&es, "self");
        Object *symAttr = Symbol_new(&es, "attr");
        Object *symNew = Symbol_new(&es, "new");
        Object *symFunction = Symbol_new(&es, "function");
        Object *symCall = Symbol_new(&es, "call");
        Object *symId = Symbol_new(&es, "id");
        Object *symSharp = Symbol_new(&es, "#");

        Object *ast = Tuple_new(&es, 2,
                                symBraces,
                                Array_new(&es, 3,
                                          Tuple_new(&es, 3,
                                                    symClass,
                                                    String_new(&es, "A"),
                                                    Tuple_new(&es, 3,
                                                              symCall,
                                                              Tuple_new(&es, 3,
                                                                        symAttr,
                                                                        Tuple_new(&es, 1,
                                                                                  symSelf),
                                                                        String_new(&es, "setMethod")),
                                                              Array_new(&es, 2,
                                                                        Tuple_new(&es, 2,
                                                                                  symSharp,
                                                                                  String_new(&es, "m")),
                                                                        Tuple_new(&es, 2,
                                                                                  symNew,
                                                                                  Tuple_new(&es, 3,
                                                                                            symAssign,
                                                                                            Tuple_new(&es, 3,
                                                                                                      symAttr,
                                                                                                      Tuple_new(&es, 1,
                                                                                                                symSelf),
                                                                                                      String_new(&es, "()")),
                                                                                            Tuple_new(&es, 4,
                                                                                                      symFunction,
                                                                                                      String_new(&es, ""),
                                                                                                      Array_new(&es, 2,
                                                                                                                String_new(&es, "this"),
                                                                                                                String_new(&es, "args")),
                                                                                                      Tuple_new(&es, 3,
                                                                                                                symCall,
                                                                                                                Tuple_new(&es, 3,
                                                                                                                          symAttr,
                                                                                                                          Tuple_new(&es, 2,
                                                                                                                                    symId,
                                                                                                                                    String_new(&es, "IO")),
                                                                                                                          String_new(&es, "writeLine")),
                                                                                                                Array_new(&es, 2,
                                                                                                                          Tuple_new(&es, 2,
                                                                                                                                    symId,
                                                                                                                                    String_new(&es, "this")),
                                                                                                                          Tuple_new(&es, 2,
                                                                                                                                    symId,
                                                                                                                                    String_new(&es, "args")))))))))),
                                          Tuple_new(&es, 3,
                                                    symAssign,
                                                    Tuple_new(&es, 2,
                                                              symId,
                                                              String_new(&es, "a")),
                                                    Tuple_new(&es, 3,
                                                              symNew,
                                                              Tuple_new(&es, 2,
                                                                        symId,
                                                                        String_new(&es, "A")),
                                                              Array_new(&es, 0))),
                                          Tuple_new(&es, 3,
                                                    symCall,
                                                    Tuple_new(&es, 3,
                                                              symAttr,
                                                              Tuple_new(&es, 2,
                                                                        symId,
                                                                        String_new(&es, "a")),
                                                              String_new(&es, "m")),
                                                    Array_new(&es, 2,
                                                              Tuple_new(&es, 2,
                                                                        symSharp,
                                                                        String_new(&es, "arg1")),
                                                              Tuple_new(&es, 2,
                                                                        symSharp,
                                                                        String_new(&es, "arg2"))))));

        printf("\n%s\n\n", String_c_str(Object_toString(&es, ast)));

        Esther_eval(&es, ast, es.root);

        printf("\n");

        const char *code = "class A {\n"
                           "    self.setMethod(\"m\", new {\n"
                           "        self.() = function(this, args) {\n"
                           "            IO.writeLine(this, args)\n"
                           "        }\n"
                           "    })\n"
                           "}\n"
                           "a = new A\n"
                           "a.m(\"arg1\", \"arg2\")";

        Esther_eval(&es, String_new(&es, code), es.root);

        printf("\n");
    }
    CATCH(e) {
        printf("error: %s\n", Exception_getMessage(e));
    }
    ENDTRY;

    return 0;
}
