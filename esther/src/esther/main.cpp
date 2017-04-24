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

    return 0;
}
