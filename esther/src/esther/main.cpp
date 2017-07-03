#include <esther.h>

#include <cstdio>

void dump_string(string str) {
    printf("data = \"%s\"; size = %zi; capacity = %zi\n", str.data, string_size(&str), string_capacity(&str));
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

    string_append_c_str(&str1, ", World!");
    string_append_str(&str4, str1);

    dump_string(str1);
    dump_string(str4);

    string_free(&str1);
    string_free(&str2);
    string_free(&str3);
    string_free(&str4);

    Esther es;
    Esther_init(&es);

    Esther_runFile(&es, argc < 2 ? "../scripts/script.es" : argv[1]);

    Esther_finalize(&es);

    return 0;
}
