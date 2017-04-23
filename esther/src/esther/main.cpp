#include <esther.h>

Object *print(Esther *esther, Object *self, Tuple *args) {
    printf("%s\n", String_c_str(Object_toString(esther, self)));
    printf("%s\n", String_c_str(Object_toString(esther, (Object *)args)));
    return self;
}

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    // if (argc < 2)
    //     return 0;

    // es::Esther esther;
    // esther.runFile(argc < 2 ? "scripts/script.es" : argv[1]);

    Esther e;
    Esther_init(&e);

    Class *_class = Class_new_init(&e, "A", NULL);

    Object *m = Object_new(&e);
    Object_setAttribute(m, "()", (Object *)Function_new(&e, "()", (Object * (*)())print, -1));

    Class_setMethod(_class, "m", (Object *)m);

    Object *obj = Class_newInstance(&e, _class);

    Object *argsData[] = { (Object *)String_new_init(&e, "arg1"), (Object *)String_new_init(&e, "arg2") };
    Tuple *args = Tuple_new_init(&e, argsData, 2);

    Object_call(&e, obj, "m", args);

    return 0;
}
