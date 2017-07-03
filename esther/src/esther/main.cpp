#include <esther.h>

#include <cstdio>

void dump_string(string str) {
    printf("data = \"%s\"\n", str.data);
    printf("size = %zi\n", string_size(&str));
    printf("capacity = %zi\n\n", string_capacity(&str));

    string_free(&str);
}

int main(int argc, const char **argv) {
    // if (argc < 2)
    //     return 0;

    string str1 = string_new("Hello, World!", 5);
    string str2 = string_new_c_str("Hello, World!");
    string str3 = string_copy(str2);
    string str4 = string_new_empty();

    dump_string(str1);
    dump_string(str2);
    dump_string(str3);
    dump_string(str4);

    Esther es;
    Esther_init(&es);

    Esther_runFile(&es, argc < 2 ? "../scripts/script.es" : argv[1]);

    Esther_finalize(&es);

    return 0;
}
